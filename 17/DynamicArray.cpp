#include "DynamicArray.h"

DynamicArray::DynamicArray(std::size_t size)
    : size_{size}, data_{new double[size]}
{
    // В версии из главы 17 элементы инициализируются нулями.
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = 0.0;
    }
}

DynamicArray::~DynamicArray()
{
    // Память, выделенная через new[], освобождается через delete[].
    delete[] data_;
}

std::size_t DynamicArray::size() const
{
    return size_;
}

double DynamicArray::get(std::size_t index) const
{
    // В первой версии проверки диапазона нет.
    // Корректные индексы: 0 .. size_-1.
    return data_[index];
}

void DynamicArray::set(std::size_t index, double value)
{
    // В первой версии проверки диапазона нет.
    data_[index] = value;
}