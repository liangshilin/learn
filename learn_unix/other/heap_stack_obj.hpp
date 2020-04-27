#pragma once
#ifndef HEAP_STACK_OBJ_HPP_
#define HEAP_STACK_OBJ_HPP_

#include <cstdlib>
#include <cstddef>
#include <new>

// ֻ���ڶ�(heap)�Ͻ����Ķ���
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

// ֻ����ջ�ϴ����Ķ���
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
