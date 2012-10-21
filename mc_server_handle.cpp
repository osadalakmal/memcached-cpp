#include "mc_server_handle.h"
#include <mc_result_handle.h>
#include <sstream>
#include <cstddef>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <snappy.h>
#include <libmemcached-1.0/struct/server.h>

using namespace com::osada;
using namespace std;

enum MEMC_FLAGS {
	COMPRESSED_FLAG = 0x01
};

template <typename Allocator>
McServerHandle<Allocator>::McServerHandle(const std::string& addr,const int port,bool auto_connect, const Allocator& alloc)
	: d_addr(addr),d_port(port), d_memc(nullptr), d_serverList(nullptr), d_isConnected(false), d_alloc(alloc)
{
	d_memc= memcached_create(NULL);
	memcached_return rc;
	d_serverList = memcached_server_list_append(d_serverList, d_addr.c_str(), d_port, &rc);
	if (auto_connect) {
		if (rc == MEMCACHED_SUCCESS) {
			doConnect();
			d_isConnected = true;
		} else {
			std::ostringstream os;
			os << "AutoConnect is on. Could not connect to the server with rc:" << rc << " errorstr: ";
			os << memcached_last_error_message(d_memc);
			memcached_server_list_free(d_serverList);
			memcached_free(d_memc);
			throw std::runtime_error(os.str());
		}
	}
}

template <typename Allocator>
McServerHandle<Allocator>::~McServerHandle()
{
	if (d_serverList) {
		memcached_server_list_free(d_serverList);
	}
	if (d_memc) {
		memcached_free(d_memc);
	}
}

template <typename Allocator>
const std::string McServerHandle<Allocator>::getAddr() const {
	return d_addr;
}

template <typename Allocator>
const int McServerHandle<Allocator>::getPort() const {
	return d_port;
}

template <typename Allocator>
const bool McServerHandle<Allocator>::isConnected() const {
	return d_isConnected;
}

template <typename Allocator>
bool McServerHandle<Allocator>::doConnect() {
	memcached_return rc = memcached_server_push(d_memc, d_serverList);
	if (rc != MEMCACHED_SUCCESS) {
		std::ostringstream os;
		os << "AutoConnect is on. Could not connect to the server with rc:" << rc << " errorstr: ";
		os << memcached_strerror(d_memc,rc);
		memcached_server_list_free(d_serverList);
		memcached_free(d_memc);
		throw std::runtime_error(os.str());
	} else {
		memcached_server_fn serverVisitor = [](const memcached_st *ptr, memcached_server_instance_st server, void *context) {
				*(reinterpret_cast<bool*>(context)) = (reinterpret_cast<const memcached_server_st*>(server)->fd != 0);
				return MEMCACHED_SUCCESS;
				};
		memcached_server_cursor (d_memc, &serverVisitor, &d_isConnected, 1);
	}
	return true;
}

template <typename Allocator>
bool McServerHandle<Allocator>::connect() {
	if (!isConnected()) {
		return doConnect();
	} else {
		return true;
	}
}

template <typename Allocator>
bool McServerHandle<Allocator>::disconnect() {
	if (isConnected()) {
		memcached_quit(d_memc);
		memcached_server_fn serverVisitor = [](const memcached_st *ptr, memcached_server_instance_st server, void *context) {
				*(reinterpret_cast<bool*>(context)) = (reinterpret_cast<const memcached_server_st*>(server)->fd != 0);
				return MEMCACHED_SUCCESS;
			};
		memcached_server_cursor (d_memc, &serverVisitor, &d_isConnected, 1);
	}
	d_isConnected = false;
	return true;
}

template <typename Allocator>
bool McServerHandle<Allocator>::storeInServer(const char* key, size_t keyLen,
	const char* data, size_t dataLen, time_t timeToExpiry, bool overwrite,bool compress) {
	assert(key); assert(data);
	assert(keyLen); assert(dataLen);
	uint32_t p_flags = 0;
	size_t compLen = dataLen;
	char* compData = const_cast<char*>(data);
	if (compress) {
		p_flags |= COMPRESSED_FLAG;
		compData = d_alloc.allocate(snappy::MaxCompressedLength(dataLen));
		snappy::RawCompress(data,dataLen,compData,&compLen);
	}
	if (overwrite) {
		return (memcached_set(d_memc,key,keyLen,compData,compLen,timeToExpiry,p_flags) == MEMCACHED_SUCCESS);
	} else {
		return (memcached_add(d_memc,key,keyLen,compData,compLen,timeToExpiry,p_flags) == MEMCACHED_SUCCESS);
	}
}

template <typename Allocator>
bool McServerHandle<Allocator>::getFromServer(const char* key, size_t keyLen, std::shared_ptr<char>& data,
		size_t& p_dataLen, uint32_t& p_flags) {
	assert(key);
	assert(keyLen);
	memcached_return_t rc;
	char *tempData = memcached_get(d_memc,key,keyLen,&p_dataLen,&p_flags,&rc);
	if (tempData == NULL || rc != MEMCACHED_SUCCESS) {
		if (rc == MEMCACHED_NOTFOUND) {
			return false;
		} else {
			std::ostringstream os;
			os << memcached_strerror(d_memc,rc);
			throw McServerException(os.str());
		}
	}
	if (p_flags & COMPRESSED_FLAG) {
		size_t uncompLen;
		snappy::GetUncompressedLength(tempData,p_dataLen,&uncompLen);
		char* uncompressedData = d_alloc.allocate(uncompLen);
		bool rc = snappy::RawUncompress(tempData,p_dataLen,uncompressedData);
		if (rc) {
			p_dataLen = uncompLen;
			data.reset(uncompressedData);
			return true;
		} else {
			return false;
		}
	}
	data.reset(tempData);
	return true;
}

template <typename Allocator>
bool McServerHandle<Allocator>::doesKeyExist(const char* key, size_t keyLen) {
	return (memcached_exist(d_memc,key,keyLen) == MEMCACHED_SUCCESS);
}

template <typename Allocator>
bool McServerHandle<Allocator>::multiGetFromServer( char* const* keys, const size_t noOfKeys,
		  size_t* keyLen, std::vector<char*>& data, std::vector<size_t> dataLen) {
	dataLen.reserve(noOfKeys);
	char return_key[MEMCACHED_MAX_KEY];
	size_t return_key_length;
	memcached_return_t ret = memcached_mget(d_memc,keys,keyLen,noOfKeys);
	if (ret == MEMCACHED_SUCCESS) {
		for (uint32_t i=0;i<noOfKeys;i++) {
			uint32_t flags;
			char* retData = memcached_fetch(d_memc,return_key,&(return_key_length),&(dataLen[i]),&flags,&ret);
			if (ret == MEMCACHED_SUCCESS) {
				data.push_back(retData);
			} else {
				dataLen[i] = 0;
			}
		}
		return true;
	} else {
		return false;
	}
}

template <typename Allocator>
bool McServerHandle<Allocator>::deleteKeyFromServer(const char* key, size_t keyLen) {
	return (memcached_delete(d_memc, key, keyLen,0) == MEMCACHED_SUCCESS);
}

template class com::osada::McServerHandle<std::allocator<char> >;