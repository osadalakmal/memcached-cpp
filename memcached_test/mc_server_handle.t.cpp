#include "../mc_server_handle.h"
#include "gtest/gtest.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <snappy.h>
#include "person.pb.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"

class McServerHandleTest : public ::testing::Test {
 protected:

	McServerHandleTest() : con_mch(SERVER_ADDR,SERVER_PORT,true)
		,uncon_mch(SERVER_ADDR,SERVER_PORT,false) {
	}

	virtual ~McServerHandleTest() {
	}

	virtual void SetUp() {
		con_mch.connect();
		uncon_mch.disconnect();
	}

	virtual void TearDown() {
	}
  
	void TestInit() {
		ASSERT_EQ(con_mch.getAddr(),SERVER_ADDR);
		ASSERT_EQ(con_mch.getPort(),SERVER_PORT);
		ASSERT_EQ(con_mch.isConnected(),true);
		ASSERT_EQ(uncon_mch.getAddr(),SERVER_ADDR);
		ASSERT_EQ(uncon_mch.getPort(),SERVER_PORT);
		ASSERT_EQ(uncon_mch.isConnected(),false);
	}

	com::osada::McServerHandle<> con_mch;
	com::osada::McServerHandle<> uncon_mch;
public:
	static const std::string SERVER_ADDR;
	static const int SERVER_PORT;
	static const char* keySimple;
	static const char* dataSimple;
};

const std::string McServerHandleTest::SERVER_ADDR = "127.0.0.1";
const int McServerHandleTest::SERVER_PORT = 11211;
const char* McServerHandleTest::keySimple = "KEYSIMPLE";
const char* McServerHandleTest::dataSimple = "DATASIMPLE";

TEST_F(McServerHandleTest,Init) {
	TestInit();
}

TEST_F(McServerHandleTest,ConnectionDisconnectionTest) {
	ASSERT_EQ(con_mch.disconnect(), true);
	ASSERT_EQ(con_mch.isConnected(), false);
	ASSERT_EQ(uncon_mch.connect(), true);
	ASSERT_EQ(uncon_mch.isConnected(),true);
	ASSERT_EQ(con_mch.connect(), true);
	ASSERT_EQ(con_mch.isConnected(), true);
}

TEST_F(McServerHandleTest,GetSetTest) {
	try {
		con_mch.storeInServer(McServerHandleTest::keySimple,strlen(McServerHandleTest::keySimple),
			McServerHandleTest::dataSimple, strlen(McServerHandleTest::dataSimple), 0, true, false);
		std::shared_ptr<char> dataOut;
		size_t dataLen;
		uint32_t p_flags;
		con_mch.getFromServer(McServerHandleTest::keySimple,strlen(McServerHandleTest::keySimple)
			,dataOut, dataLen, p_flags);
		ASSERT_EQ(memcmp(dataOut.get(),McServerHandleTest::dataSimple,strlen(McServerHandleTest::dataSimple)), 0);
		ASSERT_EQ(dataLen,strlen(McServerHandleTest::dataSimple));
	} catch (std::exception& ex) {
		std::cout << ex.what();
	}
}

TEST_F(McServerHandleTest,GetSetCompressedTest) {
	con_mch.storeInServer(McServerHandleTest::keySimple,strlen(McServerHandleTest::keySimple),
		McServerHandleTest::dataSimple, strlen(McServerHandleTest::dataSimple), 0, true, true);
	std::shared_ptr<char> dataOut;
	size_t dataLen;
	uint32_t p_flags;
	con_mch.getFromServer(McServerHandleTest::keySimple,strlen(McServerHandleTest::keySimple)
		,dataOut, dataLen, p_flags);
	ASSERT_EQ(memcmp(dataOut.get(),McServerHandleTest::dataSimple,strlen(McServerHandleTest::dataSimple)), 0);
	ASSERT_EQ(dataLen,strlen(McServerHandleTest::dataSimple));
	ASSERT_TRUE(p_flags!=0);
}

TEST_F(McServerHandleTest,CheckKeyExistAndDelete) {
	const char* key1 = "testkey1";
	con_mch.deleteKeyFromServer(key1,strlen(key1));
	ASSERT_FALSE(con_mch.doesKeyExist(key1,strlen(key1)));
	con_mch.storeInServer(key1,strlen(key1),
		McServerHandleTest::dataSimple, strlen(McServerHandleTest::dataSimple), 0, true, true);
	ASSERT_TRUE(con_mch.doesKeyExist(key1,strlen(key1)));
	ASSERT_TRUE(con_mch.deleteKeyFromServer(key1,strlen(key1)));
}

TEST_F(McServerHandleTest,MultiGet) {
	char* keys[] = {"testKey1","testKey2","testKey3"};
	size_t keyLen[] = {strlen("testKey1"),strlen("testKey2"),strlen("testKey3")};
	const char* data[] = {"testData1","testData2","testData3"};
	const size_t dataLen[] = {strlen("testData1"),strlen("testData2"),strlen("testData3")};
	con_mch.storeInServer(keys[0],keyLen[0],
		data[0], dataLen[0], 0, true, false);
	con_mch.storeInServer(keys[1],keyLen[1],
		data[1], dataLen[1], 0, true, false);
	con_mch.storeInServer(keys[2],keyLen[2],
		data[2], dataLen[2], 0, true, false);
	std::vector<size_t> retDataLen;
	std::vector<char*> retData;
	con_mch.multiGetFromServer(&keys[0],3,&keyLen[0],retData,retDataLen);
	ASSERT_EQ(strncmp(retData[0],data[0],dataLen[0]),0);
	ASSERT_EQ(strncmp(retData[1],data[1],dataLen[1]),0);
	ASSERT_EQ(strncmp(retData[2],data[2],dataLen[2]),0);
}
