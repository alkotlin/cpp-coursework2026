#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <algorithm>

template<typename T>
class DynamicArray
{
public:
    DynamicArray();
    explicit DynamicArray(std::size_t size);
    DynamicArray(std::initializer_list<T> values);

    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    std::size_t size() const { return sz_; }
    std::size_t capacity() const { return capacity_; }

    void reserve(std::size_t newalloc);
    void resize(std::size_t newsize, const T& val = T());
    void push_back(const T& val);
    bool empty() const { return sz_ == 0; }
    void clear() noexcept;
    void pop_back();

    T& operator[](std::size_t index) { return elem_[index]; }
    const T& operator[](std::size_t index) const { return elem_[index]; }

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

private:
    T* elem_;
    std::size_t sz_;
    std::size_t capacity_;
    std::allocator<T> alloc_;

    void destroy_elements();
};

template<typename T>
DynamicArray<T>::DynamicArray()
    : elem_{nullptr}, sz_{0}, capacity_{0}
{
}

template<typename T>
DynamicArray<T>::DynamicArray(std::size_t size)
    : elem_{nullptr}, sz_{size}, capacity_{size}
{
    elem_ = alloc_.allocate(capacity_);
    std::size_t i = 0;
    try
    {
        for (; i < sz_; ++i)
        {
            alloc_.construct(elem_ + i, T{});
        }
    }
    catch (...)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            alloc_.destroy(elem_ + j);
        }
        alloc_.deallocate(elem_, capacity_);
        throw;
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> values)
    : elem_{nullptr}, sz_{values.size()}, capacity_{values.size()}
{
    elem_ = alloc_.allocate(capacity_);
    std::size_t i = 0;
    try
    {
        for (const T& v : values)
        {
            alloc_.construct(elem_ + i, v);
            ++i;
        }
    }
    catch (...)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            alloc_.destroy(elem_ + j);
        }
        alloc_.deallocate(elem_, capacity_);
        throw;
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : elem_{nullptr}, sz_{other.sz_}, capacity_{other.sz_}
{
    elem_ = alloc_.allocate(capacity_);
    std::size_t i = 0;
    try
    {
        for (; i < sz_; ++i)
        {
            alloc_.construct(elem_ + i, other.elem_[i]);
        }
    }
    catch (...)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            alloc_.destroy(elem_ + j);
        }
        alloc_.deallocate(elem_, capacity_);
        throw;
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
    : elem_{other.elem_}, sz_{other.sz_}, capacity_{other.capacity_}
{
    other.elem_ = nullptr;
    other.sz_ = 0;
    other.capacity_ = 0;
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
    destroy_elements();
    alloc_.deallocate(elem_, capacity_);
}

template<typename T>
void DynamicArray<T>::destroy_elements()
{
    for (std::size_t i = 0; i < sz_; ++i)
    {
        alloc_.destroy(elem_ + i);
    }
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
    if (this == &other)
    {
        return *this;
    }

    T* new_elem = alloc_.allocate(other.sz_);
    std::size_t i = 0;
    try
    {
        for (; i < other.sz_; ++i)
        {
            alloc_.construct(new_elem + i, other.elem_[i]);
        }
    }
    catch (...)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            alloc_.destroy(new_elem + j);
        }
        alloc_.deallocate(new_elem, other.sz_);
        throw;
    }

    destroy_elements();
    alloc_.deallocate(elem_, capacity_);

    elem_ = new_elem;
    sz_ = other.sz_;
    capacity_ = other.sz_;

    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    destroy_elements();
    alloc_.deallocate(elem_, capacity_);

    elem_ = other.elem_;
    sz_ = other.sz_;
    capacity_ = other.capacity_;

    other.elem_ = nullptr;
    other.sz_ = 0;
    other.capacity_ = 0;

    return *this;
}

template<typename T>
void DynamicArray<T>::reserve(std::size_t newalloc)
{
    if (newalloc <= capacity_)
    {
        return;
    }

    T* new_elem = alloc_.allocate(newalloc);
    std::size_t i = 0;
    try
    {
        for (; i < sz_; ++i)
        {
            alloc_.construct(new_elem + i, elem_[i]);
        }
    }
    catch (...)
    {
        for (std::size_t j = 0; j < i; ++j)
        {
            alloc_.destroy(new_elem + j);
        }
        alloc_.deallocate(new_elem, newalloc);
        throw;
    }

    for (std::size_t j = 0; j < sz_; ++j)
    {
        alloc_.destroy(elem_ + j);
    }

    alloc_.deallocate(elem_, capacity_);

    elem_ = new_elem;
    capacity_ = newalloc;
}

template<typename T>
void DynamicArray<T>::resize(std::size_t newsize, const T& val)
{
    if (newsize > sz_)
    {
        reserve(newsize);
        for (std::size_t i = sz_; i < newsize; ++i)
        {
            alloc_.construct(elem_ + i, val);
        }
    }
    else if (newsize < sz_)
    {
        for (std::size_t i = newsize; i < sz_; ++i)
        {
            alloc_.destroy(elem_ + i);
        }
    }
    sz_ = newsize;
}

template<typename T>
void DynamicArray<T>::push_back(const T& val)
{
    if (capacity_ == 0)
    {
        reserve(8);
    }
    else if (sz_ == capacity_)
    {
        reserve(2 * capacity_);
    }
    alloc_.construct(elem_ + sz_, val);
    ++sz_;
}

template<typename T>
T& DynamicArray<T>::at(std::size_t index)
{
    if (index >= sz_)
    {
        throw std::out_of_range("DynamicArray: index out of range");
    }
    return elem_[index];
}

template<typename T>
const T& DynamicArray<T>::at(std::size_t index) const
{
    if (index >= sz_)
    {
        throw std::out_of_range("DynamicArray: index out of range");
    }
    return elem_[index];
}
template<typename T>
void DynamicArray<T>::clear() noexcept
{
    destroy_elements();
    sz_ = 0;
}

template<typename T>
void DynamicArray<T>::pop_back()
{
    if (sz_ == 0)
    {
        throw std::out_of_range("DynamicArray: pop_back from empty vector");
    }
    --sz_;
    alloc_.destroy(elem_ + sz_);
}