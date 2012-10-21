#ifndef MCSERVERHANDLE_H
#define MCSERVERHANDLE_H

#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <libmemcached/memcached.h>
#include <snappy.h>

namespace com {
namespace osada {

/**
 * @class McServerException
 * @author Osada Paranaliyanage
 * @date 30/09/12
 * @file mc_server_handle.h
 * @brief This class is thrown on any unhandled errors from this library
 */
class McServerException : std::runtime_error {
public:
	McServerException(const std::string& what) : std::runtime_error(what) {}
};
	
/**
 * @class McServerHandle
 * @author Osada Paranaliyanage
 * @date 29/09/12
 * @file mc_server_handle.h
 * @brief This class represents a handle for a connection to a given memcached server.
 * 		  There can only be one connection to a given server. If multiple memcacehed servers are running
 * 		  on a given host then multiple handle objects can be created to that server
 */
template <typename Allocator = std::allocator<char> >
class McServerHandle
{
	friend class McServerHandleTest;
	
	std::string d_addr;
	int			d_port;
	memcached_st *d_memc;
	memcached_server_st* d_serverList;
	bool		d_isConnected;
	Allocator	d_alloc;
	
	bool doConnect();
	
public:

	//typedef std::function<void (memcached_result_st *,memcached_st *, memcached_result_st *, memcached_return_t *)>;

	/**
	 * @brief Constructor taking hostname and port no of the memcached server
	 *  	  note that the hostname should not be an ip address
	 */
	McServerHandle(const std::string& addr,const int port,bool auto_connect=true, const Allocator& alloc = std::allocator<char>() );
	virtual ~McServerHandle();
	
	/**
	 * @brief returns the address of the server this connects to
	 */
	const std::string getAddr() const ;
	/**
	 * @brief return the port on the server that this connects to.
	 */
	const int getPort() const ;
	/**
	 * @brief return if this is connected or not to the memcached server
	 */
	const bool isConnected() const;	
	
	/**
	 * @brief Establish a connection to the memcached server
	 */
	bool connect();
	/**
	 * @brief Disconnect from the server and free memcached_st structures
	 */
	bool disconnect();
	
	/**
	 * @brief Write a given value to a memcached server we are connected to at the time
	 * @param key	The key used to refer to the value
	 * @param keyLen	Length of the key
	 * @param data	The data to be stored on the server
	 * @param dataLen	Length of the data
	 * @param overwrite	if to overwrite the data for a given key at the server if it already exists
	 * @return true if the store succeeded
	 */
	bool storeInServer(const char* key, size_t keyLen, const char* data, size_t dataLen, time_t timeToExpiry, bool overwrite, bool compress);
	
	/**
	 * @brief This method retrieves a value for a given key from the memcached server
	 * @param key	The key used to refer to the value
	 * @param keyLen	Length of the key
	 * @param data	The data to be stored on the server
	 * @param dataLen	Length of the data
	 * @param p_flags
	 * @return 
	 */
	bool getFromServer(const char* key, size_t keyLen, std::shared_ptr<char>& data,
			size_t& p_dataLen, uint32_t& p_flags);
			
	/**
	 * @brief This method allows you get retrieve a set of data corresponding to multiple keys from the server
	 * @param keys	The keys used to refer to the value
	 * @param keyLen	Lengths of the keys
	 * @param noOfKeys The number of keys in the data set
	 * @param data The result vector used to reutrn the data
	 * @param dataLen The reuslt vector used to return the data lengths
	*/
	bool multiGetFromServer( char*const* keys, const size_t noOfKeys, uint32_t* keyLen,
			std::vector<char*>& data,  std::vector<size_t> dataLen);
	
	/**
	 * @brief This method allows you to check if a certain key exists on the server
	 * @param keys	The keys for which the check is done
	 * @param keyLen The length of the key
	 */
	 bool doesKeyExist(const char* key, size_t keyLen);
	 
	 /**
	  * @brief This method removes a key and associated value from a server
	  * @param key This is the key that will be removed from the server
	  * @param keyLen The length of the key
	  */
	 bool deleteKeyFromServer(const char* key, size_t keyLen);
};

}
}

#endif // MCSERVERHANDLE_H
