#include <iostream>
#include <ctime>

int main()
{
    long long val = 1'234'567'891'011'121'345;
    std::cout << "val = " << val << '\n';
    double conv = val;
    val = conv;
    std::cout << "val = " << val << '\n';
    return 0;
}