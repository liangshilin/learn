#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <array>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <iostream>

#define  ARRAY_SIZE  10000

using namespace std;

template <typename T>
class STLContainer
{
public:

	STLContainer() = default;
	virtual ~STLContainer() = default;

	void array_test(const T& value)
	{
		cout << "array fill " << value << endl;
		array_.fill(value);

		int i = 0;
		for (auto iter = array_.begin(); iter != array_.end(); iter++)
		{
			*iter = i++;
			cout << "array element is " << *iter << endl;
		}

		cout << "array size " << array_.size() << endl;
		cout << "array max size is " << array_.max_size() << endl;
		cout << "array is empty: " << array_.empty() << endl;
		cout << "array at(0) element is " << array_.at(0) << endl;
		cout << "array [0] element is " << array_[0] << endl;
		cout << "array front element is " << array_.front() << endl;
		cout << "array data is " << array_.data() << " and value is " << *array_.data() << endl;

		for (auto iter = array_.rbegin(); iter != array_.rend(); iter++)
		{
			cout << "array element is " << *iter << endl;
		}
	}

	void vector_test(const T& value)
	{
		cout << "vector assign 10000 element " << value << endl;
		vector_.assign(10000, value);

		int i = 0;
		for (auto iter = vector_.begin(); iter != vector_.end(); iter++)
		{
			*iter = i++;
		}

		cout << "vector size is " << vector_.size() << endl;
		cout << "vector max size is " << vector_.max_size() << endl;
		cout << "vector capacity is " << vector_.capacity() << endl;
		cout << " reserve vector size 100000" << endl;
		vector_.reserve(100000);
		auto alloca = vector_.get_allocator();
		std::swap(vector_, vector_);

	}

	void forward_list_test()
	{
		forward_list_.sort();
	}

private:

private:
	array<T, ARRAY_SIZE> array_;
	vector<T> vector_;
	map<string, T> map_;
	deque<T> deque_;
	list<T> list_;
	forward_list<T> forward_list_;
	set<T> set_;
	unordered_set<T> unordered_set_;
	unordered_map<string, T> unordered_map_;
};

#endif
