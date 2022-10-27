#include <iostream>
#include <ctime>
#include <cmath>

double int_pow(double x, int deg)
{
    double res = 1;
    for (int it = 0; it < deg;++it)
        res *= x;
    return res;
}

int main()
{
    int degree;
    std::cin >> degree;
    double x = 0.5;
    clock_t start = clock();
    double res = std::pow(x, degree);
    clock_t fin = clock();
    std::cout << "pow elapsed " << 1000*(double)(fin-start)/CLOCKS_PER_SEC << " ms\n";
    std::cout << "res = " << res << '\n';

    start = clock();
    res = int_pow(x, degree);
    fin = clock();
    std::cout << "int_pow elapsed " << 1000*(double)(fin-start)/CLOCKS_PER_SEC << " ms\n";
    std::cout << "res = " << res << '\n';

    return 0;
}