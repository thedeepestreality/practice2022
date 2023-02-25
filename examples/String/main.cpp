#include <iostream>
#include "String.h"

int main()
{
    String str1("123");
    String str2("abcde");
    str1.print();
    str2.print();
    str2 += str1;
    str2.print();
    String sum = str1 + str2;
    sum.print();

    std::cout << (String("123") <  String("223")) << '\n';
    std::cout << (String("123") >  String("223")) << '\n';
    std::cout << (String("123") <= String("123")) << '\n';
    std::cout << (String("123") >= String("123")) << '\n';
    std::cout << (String("123") == String("123")) << '\n';
    std::cout << (String("123") != String("223")) << '\n';


    system("pause");
    return 0;
}