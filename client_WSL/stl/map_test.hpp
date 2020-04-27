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

	// 测试容易搞混的成员函数
	void start()
	{
		//清除map数据
		data_.clear();

		//生成测试数据
		generate_test_date();

		for (const auto& key_value : data_)
		{
			cout << format("key:%d, value:%s") % key_value.first % key_value.second << endl;
		}

		//不存在键值抛出out_of_range异常
		try{
			cout << format("key:%d, value:%s") % data_.at(data_.size()) << endl;
		}
		catch (out_of_range){
			cout << format("out of range[%d]") % data_.size() << endl;
		}
			
		//max_size = 
		cout << format("max_size: %d") % data_.max_size() << endl;

		//迭代器删除map元素，注意删除元素后，迭代器失效，erase返回删除元素的后一个元素的迭代器
		//e.g. delete key=55 element
		for (auto iter = data_.begin(); iter != data_.end(); )
		{
			if (55 == iter->first)
			{
				//iter此时等于下一个元素的迭代器
				cout << format("erase start element=[%d:%s]") % iter->first % iter->second << endl;
				iter = data_.erase(iter);
				cout << format("erase finish element=[%d:%s]") % iter->first % iter->second << endl;
			}
			else
			{
				iter++;
			}
		}

		//erase(key)删除元素，存在key则返回1，不存在则返回0
		cout << format("again erase key=55 element, erase element num=[%d]") % data_.erase(55) << endl;

		//此时map不存在key=55的元素，所以返回0，否则返回1
		cout << format("count of key=55 element num=[%d]") % data_.count(55) << endl;

		// find比count更高级，元素存在返回指向元素的迭代器，否则返回end()迭代器
		auto find_iter = data_.find(55);
		if (find_iter != data_.end())
		{
			cout << format("key=55 element exist [%d:%s]") % find_iter->first % find_iter->second << endl;
		}
		else
		{
			cout << format("key=55 element is not exist") << endl;
		}

		// emplace原位构造元素，map不存在key则插入传入参数构造的元素
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
