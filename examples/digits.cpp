#include <iostream>

int main() 
{
    std::cout << "input val: ";
    int val;
    std::cin >> val;
    int val_copy = val;
    int sum = 0;
    int prod = 1;
    int digit;
    int degree = 1;
    //compute sum and product of the integer value
    while (val != 0)
    {
        digit = val%10;
        sum += digit;
        prod *= digit;
        val /= 10;
        degree *= 10;
    }

    //output value digit by digit
    while (degree != 1)
    {
        degree /= 10;
        std::cout << val_copy / degree;
        val_copy %= degree;
    }

    std::cout << "\nsum = " << sum << '\n';
    std::cout << "prod = " << prod << '\n';
    return 0;
}