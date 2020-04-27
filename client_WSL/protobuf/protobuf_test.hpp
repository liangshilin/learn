#pragma once
#ifndef PROTOBUF_PROTOBUF_TEST_HPP_
#define PROTOBUF_PROTOBUF_TEST_HPP_

#include "message.pb.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace test;

class ProtobufTest
{
public:
	ProtobufTest();
	~ProtobufTest();

	void test()
	{
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		//写入
		Person person1;
		person1.set_name("liangshilin");
		person1.set_age(28);
		person1.set_id(1);
		person1.set_gender(Person::MAN);
		person1.set_email("liangshilin_lsl@outlook.com");
		auto child1 = person1.add_childer();
		child1->set_id(2);
		child1->set_name("xxx1");
		auto child2 = person1.add_childer();
		child2->set_name("xxx2");
		child2->set_id(3);
		cout << "person1 serialize size is " << person1.ByteSize() << endl;
		auto result = person1.SerializeAsString();

		//序列发长度(字符串)
		char size[5] = { 0 };
		sprintf(size, "%04x", person1.ByteSize());
		sprintf(size, "%04x", 65535);
		auto size_int = strtol(size, nullptr, 16);

		//读取
		Person person2;
		person2.ParseFromString(result);
		cout << person2.name() << endl;
		cout << person2.age() << endl;
		cout << person2.id() << endl;
		cout << Person::Gender_Name(person2.gender()) << endl;
		cout << person2.email() << endl;
		auto child3 = person2.childer(0);
		cout << child3.name() << endl;
		cout << child3.id() << endl;
		
		google::protobuf::ShutdownProtobufLibrary();
	}

private:

};

ProtobufTest::ProtobufTest()
{
}

ProtobufTest::~ProtobufTest()
{
}

#endif // !PROTOBUF_PROTOBUF_TEST_HPP_

