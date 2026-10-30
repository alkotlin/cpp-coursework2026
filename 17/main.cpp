#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray v(5);

    std::cout << "size = " << v.size() << '\n';

    std::cout << "initial values: ";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v.get(i) << ' ';
    }
    std::cout << '\n';

    for (std::size_t i = 0; i < v.size(); ++i)
    {
        v.set(i, 1.1 * static_cast<double>(i + 1));
    }

    std::cout << "after set: ";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v.get(i) << ' ';
    }
    std::cout << '\n';

    v.set(2, 42.5);
    std::cout << "v.get(2) = " << v.get(2) << '\n';

    return 0;
}