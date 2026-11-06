#include <iostream>
#include <string>
#include "DynamicArray.h"

void print(const DynamicArray<int>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    // 1. Создание с размером
    DynamicArray<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    std::cout << "a: ";
    print(a);

    // 2. Список инициализации
    DynamicArray<double> b{1.5, 2.5, 13.0};
    std::cout << "b: ";
    for (std::size_t i = 0; i < b.size(); ++i)
    {
        std::cout << b[i] << ' ';
    }
    std::cout << '\n';

    // 3. push_back и capacity
    DynamicArray<int> c;
    std::cout << "c.size=" << c.size() << ", c.capacity=" << c.capacity() << '\n';
    for (int i = 0; i < 10; ++i)
    {
        c.push_back(i * 10);
    }
    std::cout << "c: ";
    print(c);
    std::cout << "c.size=" << c.size() << ", c.capacity=" << c.capacity() << '\n';

    // 4. resize
    c.resize(5);
    std::cout << "after resize(5): ";
    print(c);
    c.resize(8, 99);
    std::cout << "after resize(8, 99): ";
    print(c);

    // 5. reserve
    DynamicArray<int> d;
    d.reserve(20);
    std::cout << "d.size=" << d.size() << ", d.capacity=" << d.capacity() << '\n';

    // 6. at и исключения
    try
    {
        std::cout << c.at(100) << '\n';
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "exception: " << e.what() << '\n';
    }

    // 7. Копирование и присваивание
    DynamicArray<int> e = c;
    e[0] = 1000;
    std::cout << "c[0]=" << c[0] << ", e[0]=" << e[0] << '\n';

    DynamicArray<int> f(2);
    f = c;
    f = f;
    std::cout << "f: ";
    print(f);

    // 8. Перемещение
    DynamicArray<int> g = std::move(e);
    std::cout << "g.size=" << g.size() << ", e.size=" << e.size() << '\n';

    // 9. Шаблон с std::string
    DynamicArray<std::string> words{"one", "two", "three"};
    words.push_back("four");
    for (std::size_t i = 0; i < words.size(); ++i)
    {
        std::cout << words[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}