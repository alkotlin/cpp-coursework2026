#include "DynamicArray.h"

DynamicArray::DynamicArray(std::size_t size)
    : size_{size}, data_{new double[size]}
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = 0.0;
    }
}

DynamicArray::~DynamicArray()
{
    delete[] data_;
}

std::size_t DynamicArray::size() const
{
    return size_;
}

double DynamicArray::get(std::size_t index) const
{
    return data_[index];
}

void DynamicArray::set(std::size_t index, double value)
{
    data_[index] = value;
}