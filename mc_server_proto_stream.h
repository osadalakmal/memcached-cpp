#ifndef INCLUDED_MC_SERVER_PROTO_STREAM_H
#define INCLUDED_MC_SERVER_PROTO_STREAM_H
#include <vector>
#include <stdint.h>
#include <mutex>
#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace com {
namespace osada {
	
class McServerProtoInputStream : public google::protobuf::io::ZeroCopyInputStream {
private:
	McServerProtoInputStream(const McServerProtoInputStream& rhs);
	McServerProtoInputStream& operator=(const McServerProtoInputStream& rhs);
	std::timed_mutex d_mutex;
	size_t reserveSize;
	std::vector<uint8_t> d_data;

	static const int DEFAULT_SIZE = 1024;
	google::protobuf::io::ArrayInputStream d_aiStream;
public:
	McServerProtoInputStream();
	virtual ~McServerProtoInputStream();
	virtual std::vector<uint8_t>& getBuffer() { return d_data; }
	virtual bool Next(const void** data, int* size);
	virtual void BackUp(int count);
	virtual bool Skip(int count);
	virtual int64_t ByteCount() const ;
};

class McServerProtoOutputStream : public google::protobuf::io::ZeroCopyOutputStream {
private:
	McServerProtoOutputStream(const McServerProtoOutputStream& rhs);
	McServerProtoOutputStream& operator=(const McServerProtoOutputStream& rhs);
	std::timed_mutex d_mutex;
	size_t reserveSize;
	std::vector<uint8_t> d_data;

	static const int DEFAULT_SIZE = 1024;
	google::protobuf::io::ArrayOutputStream d_aoStream;
public:
	McServerProtoOutputStream();
	virtual ~McServerProtoOutputStream();
	virtual std::vector<uint8_t>& getBuffer() { return d_data; }
	virtual bool Next(void** data, int* size);
	virtual void BackUp(int count);
	virtual int64_t ByteCount() const ;
};

}
}
#endif // INCLUDED_MC_SERVER_PROTO_STREAM_H
