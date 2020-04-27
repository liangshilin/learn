#pragma once
#ifndef HEAP_STACK_OBJ_HPP_
#define HEAP_STACK_OBJ_HPP_

#include <cstdlib>
#include <cstddef>
#include <new>

// 只能在堆(heap)上建立的对象
class OnlyHeap
{
public: 
    void Destory()
    {
        delete this;
    }

    static OnlyHeap* Create()
    {
        return new OnlyHeap();
    }

protected:
    OnlyHeap() = default;
    virtual ~OnlyHeap() = default;

};

// 只能在栈上创建的对象
class OnlyStack
{
public:
	OnlyStack() = default;
	~OnlyStack() = default;

protected:
    void* operator new (size_t size) noexcept
    {
        ::operator new(size);
    }

    void operator delete(void* ptr) noexcept
    {
        ::operator delete(ptr);
    }

    void* operator new[](size_t size) noexcept
    {
        ::operator new[](size);
    }

    void operator delete[](void* ptr) noexcept
    {
        ::operator delete[](ptr);
    }
};

#endif // !HEAP_STACK_OBJ_HPP_
