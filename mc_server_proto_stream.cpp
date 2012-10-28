#include "mc_server_proto_stream.h"

namespace com {
namespace osada {

McServerProtoInputStream::McServerProtoInputStream() : reserveSize(DEFAULT_SIZE),
	d_data(reserveSize), d_aiStream(&(d_data[0]),reserveSize) {
}

McServerProtoInputStream::~McServerProtoInputStream() {
}

bool McServerProtoInputStream::Next(const void** data, int* size) {
	return d_aiStream.Next(data, size);
}

void McServerProtoInputStream::BackUp(int count) {
	return d_aiStream.BackUp(count);
}

bool McServerProtoInputStream::Skip(int count) {
	return d_aiStream.Skip(count);
}

int64_t McServerProtoInputStream::ByteCount() const {
	return d_aiStream.ByteCount();
}

McServerProtoOutputStream::McServerProtoOutputStream() : reserveSize(DEFAULT_SIZE),
	d_data(reserveSize), d_aoStream(static_cast<void*>(&(d_data[0])),reserveSize) {
}

McServerProtoOutputStream::~McServerProtoOutputStream() {
}

bool McServerProtoOutputStream::Next(void** data, int* size) {
	return d_aoStream.Next(data, size);
}

void McServerProtoOutputStream::BackUp(int count) {
	return d_aoStream.BackUp(count);
}

int64_t McServerProtoOutputStream::ByteCount() const {
	return d_aoStream.ByteCount();
}


}
}

