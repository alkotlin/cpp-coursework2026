#include "DynamicArray.h"
#include <algorithm>

DynamicArray::DynamicArray(std::size_t size)
    : size_{size}, data_{new double[size]}
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = 0.0;
    }
}

DynamicArray::DynamicArray(std::initializer_list<double> values)
    : size_{values.size()}, data_{new double[values.size()]}
{
    std::copy(values.begin(), values.end(), data_);
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : size_{other.size_}, data_{new double[other.size_]}
{
    std::copy(other.data_, other.data_ + size_, data_);
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept
    : size_{other.size_}, data_{other.data_}
{
    other.size_ = 0;
    other.data_ = nullptr;
}

DynamicArray::~DynamicArray()
{
    delete[] data_;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
    if (this == &other)
    {
        return *this;
    }

    double* new_data = new double[other.size_];
    std::copy(other.data_, other.data_ + other.size_, new_data);

    delete[] data_;
    data_ = new_data;
    size_ = other.size_;

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;

    return *this;
}

std::size_t DynamicArray::size() const
{
    return size_;
}

double& DynamicArray::operator[](std::size_t index)
{
    return data_[index];
}

double DynamicArray::operator[](std::size_t index) const
{
    return data_[index];
}