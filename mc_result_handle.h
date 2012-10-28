#ifndef INCLUDED_MC_RESULT_HANDLE
#define INCLUDED_MC_RESULT_HANDLE

#include <memory>
#include <libmemcached/memcached.h>

namespace com
{

namespace osada
{

class McResultHandle
{
	//std::allocator d_allocator;
	memcached_result_st *d_result;
public:
	McResultHandle(const memcached_st* p_memc) {
		if (memcached_result_create(p_memc,d_result) == NULL) {
			throw std::runtime_error("Could not allocate memcached result st");
		}
	}
	virtual ~McResultHandle() {
		memcached_result_free(d_result);
	}
	
	const char * keyValue() {
		return memcached_result_key_value(d_result);
	}
	
	size_t keyLength() {
		return memcached_result_key_length(d_result);
	}
	
	const char * resultValue() {
		return memcached_result_value(d_result);
	}
	
	size_t resultLen() {
		return memcached_result_length(d_result);
	}
	
	uint32_t resultFlags() {
		return memcached_result_flags(d_result);
	}
	
	uint64_t resultCAS() {
		return memcached_result_cas(d_result);
	}
	
	memcached_return_t setValue(const char *p_value, size_t p_length) {
		return memcached_result_set_value(d_result, p_value, p_length);
	}
	
	void setFlags(uint32_t flags) {
		memcached_result_set_flags(d_result, flags);
	}
	
	void setExpiration(time_t timeToExp) {
		memcached_result_set_expiration(d_result, timeToExp);	
	}

};

}

}

#endif // INCLUDED_MC_RESULT_HANDLE
