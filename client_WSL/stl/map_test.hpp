#pragma once
#ifndef STL_MAP_HPP_
#define STL_MAP_HPP_

#include <map>
#include <string>
#include <iostream>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

class StlMapTest
{
public:
	StlMapTest();
	virtual ~StlMapTest();

	void generate_test_date(int num = 100)
	{
		for (int i = 0; i < num; i++)
		{
			data_.insert(make_pair(i, (format("value_%d") % i).str()));
		}
	}

	// �������׸��ĳ�Ա����
	void start()
	{
		//���map����
		data_.clear();

		//���ɲ�������
		generate_test_date();

		for (const auto& key_value : data_)
		{
			cout << format("key:%d, value:%s") % key_value.first % key_value.second << endl;
		}

		//�����ڼ�ֵ�׳�out_of_range�쳣
		try{
			cout << format("key:%d, value:%s") % data_.at(data_.size()) << endl;
		}
		catch (out_of_range){
			cout << format("out of range[%d]") % data_.size() << endl;
		}
			
		//max_size = 
		cout << format("max_size: %d") % data_.max_size() << endl;

		//������ɾ��mapԪ�أ�ע��ɾ��Ԫ�غ󣬵�����ʧЧ��erase����ɾ��Ԫ�صĺ�һ��Ԫ�صĵ�����
		//e.g. delete key=55 element
		for (auto iter = data_.begin(); iter != data_.end(); )
		{
			if (55 == iter->first)
			{
				//iter��ʱ������һ��Ԫ�صĵ�����
				cout << format("erase start element=[%d:%s]") % iter->first % iter->second << endl;
				iter = data_.erase(iter);
				cout << format("erase finish element=[%d:%s]") % iter->first % iter->second << endl;
			}
			else
			{
				iter++;
			}
		}

		//erase(key)ɾ��Ԫ�أ�����key�򷵻�1���������򷵻�0
		cout << format("again erase key=55 element, erase element num=[%d]") % data_.erase(55) << endl;

		//��ʱmap������key=55��Ԫ�أ����Է���0�����򷵻�1
		cout << format("count of key=55 element num=[%d]") % data_.count(55) << endl;

		// find��count���߼���Ԫ�ش��ڷ���ָ��Ԫ�صĵ����������򷵻�end()������
		auto find_iter = data_.find(55);
		if (find_iter != data_.end())
		{
			cout << format("key=55 element exist [%d:%s]") % find_iter->first % find_iter->second << endl;
		}
		else
		{
			cout << format("key=55 element is not exist") << endl;
		}

		// emplaceԭλ����Ԫ�أ�map������key����봫����������Ԫ��
		auto emplace_result = data_.emplace(55, "value_55");
		if (emplace_result.second)
		{
			cout << format("emplace(55,\"value_555\") sucessful") << endl;
		}
		else
		{
			cout << format("emplace(55,\"value_555\") fail, map still have [%d:%s]") %
				emplace_result.first->first % emplace_result.first->second << endl;
		}
		
	}

private:
	map<int, string> data_;
};

StlMapTest::StlMapTest()
{
}

StlMapTest::~StlMapTest()
{
}


#endif // !STL_MAP_HPP_
