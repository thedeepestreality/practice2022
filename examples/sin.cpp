#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>

double fact(int count)
{
    double res = 1;
    for (int i = 2; i <= count; ++i)
        res *= i;
    return res;
}

int main()
{
    double x;
    int max_steps;
    std::cout << "Input x: ";
    std::cin >> x >> max_steps;
    double sum = 0;
    int count = 0;
    clock_t start = std::clock();
    while (count < max_steps){
        int deg = 2*count+1;
        sum += std::pow(-1, count++)*std::pow(x, deg)/fact(deg);
    } 
    clock_t fin = std::clock();
    std::cout << "func time passed: " << 1000*(double)(fin - start)/CLOCKS_PER_SEC << " ms\n";
    std::cout << std::setprecision(8) << std::sin(x) << " " << sum << '\n';

    count = 1;
    sum = 0;
    double curr = x;
    start = std::clock();
    do {
        sum += curr;
        int deg = 2*count+1;
        curr *= -x*x/(deg*(deg-1));
    } while (++count <= max_steps);
    fin = std::clock();
    std::cout << "rec time passed: " << 1000*(double)(fin - start)/CLOCKS_PER_SEC << " ms\n";
    std::cout << std::setprecision(8) << std::sin(x) << " " << sum << '\n';

    return 0;
}