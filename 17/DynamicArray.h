#pragma once

#include <cstddef>

// Первая версия "вектора" по главе 17:
// очень упрощённый динамический массив double.
// НЕТ: шаблонов, operator[], исключений, копирования, push_back/resize.
class DynamicArray
{
public:
    explicit DynamicArray(std::size_t size);
    ~DynamicArray();

    std::size_t size() const;

    double get(std::size_t index) const;
    void set(std::size_t index, double value);

private:
    std::size_t size_;
    double* data_;
};