#include <iostream>
#include "DynamicArray.h"

void print(const DynamicArray& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    DynamicArray v1(3);
    v1[0] = 1.1;
    v1[1] = 2.2;
    v1[2] = 3.3;

    std::cout << "v1: ";
    print(v1);

    DynamicArray v2{10.0, 20.0, 30.0};
    std::cout << "v2: ";
    print(v2);

    DynamicArray v3 = v2;
    v3[0] = 99.0;
    std::cout << "v2[0] = " << v2[0]
              << ", v3[0] = " << v3[0] << '\n';

    DynamicArray v4(2);
    v4[0] = -1.0;
    v4 = v1;
    v4[1] = 77.0;
    std::cout << "v1[1] = " << v1[1]
              << ", v4[1] = " << v4[1] << '\n';

    v4 = v4;
    std::cout << "v4 size after self-assignment: "
              << v4.size() << '\n';

    DynamicArray v5(std::move(v3));
    std::cout << "v5 size = " << v5.size()
              << ", v3 size = " << v3.size() << '\n';

    DynamicArray v6(1);
    v6 = std::move(v5);
    std::cout << "v6 size = " << v6.size()
              << ", v5 size = " << v5.size() << '\n';

    const DynamicArray& cv = v1;
    std::cout << "cv[0] = " << cv[0] << '\n';

    return 0;
}