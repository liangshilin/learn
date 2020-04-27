
#ifndef VIRTUAL_TEST_H_
#define VIRTUAL_TEST_H_

#include <iostream>
#include <mutex>

using namespace std;

class father
{
public:
	father() = default;
	//virtual ~father() = default;

	virtual void one()
	{
		cout << "father one" << endl;
	}

	virtual void two()
	{
		cout << "father two" << endl;
	}

private:

};

class children :public father
{
public:
	children():father() {};
	//virtual ~children() {};

	virtual void one() override
	{
		cout << "children one" << endl;
	}

	virtual void three()
	{
		cout << "children three" << endl;
	}
private:

};



class VirtualTest
{
	typedef void(*func)(void);
public:
	VirtualTest() = default;
	virtual ~VirtualTest() = default;

	void test()
	{
		children child;
		func one = (func)*((int*)*(int*)(&child) + 0);
		func two = (func)*((int*)*(int*)(&child) + 2);
		func three = (func)*((int*)*(int*)(&child) + 4);

		one();
		two();
		three();
	}
};


#endif // !VIRTUAL_TEST_H_
