#include "../mc_server_proto_stream.h"
#include "gtest/gtest.h"
#include "person.pb.h"
#include <algorithm>

using namespace com::osada;

TEST(Protobuf,SimplePB) {
	using namespace std;
	using namespace google::protobuf::io;
	Person person;
	person.set_id(12345);
	person.set_name("Osada");
	person.set_email("osada@example.com");
	McServerProtoOutputStream mcOutStream;

	person.SerializeToZeroCopyStream(dynamic_cast<ZeroCopyOutputStream*>(&mcOutStream));
	McServerProtoInputStream mcInpStream;
	std::vector<uint8_t>& dataVec = mcOutStream.getBuffer();
	std::copy(dataVec.begin(),dataVec.end(),mcInpStream.getBuffer().begin());
	Person p2;
	p2.ParseFromZeroCopyStream(&mcInpStream);
	ASSERT_EQ(p2.name(),person.name());
	ASSERT_EQ(p2.id(),person.id());
	ASSERT_EQ(p2.email(),person.email());
}