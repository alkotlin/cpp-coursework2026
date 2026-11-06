#pragma once

#include <cstddef>
#include <initializer_list>

class DynamicArray
{
public:
    explicit DynamicArray(std::size_t size);
    DynamicArray(std::initializer_list<double> values);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    std::size_t size() const;

    double& operator[](std::size_t index);
    double operator[](std::size_t index) const;

private:
    std::size_t size_;
    double* data_;
};