#include "utils.h"
#include <iostream>

inline void shout(){
    std::cout << "utils\n";
}

void test_inline()
{
    shout();
}

int** createMatrix(int rows, int cols)
{
    int** arr = new int*[rows];
    for (int r=0; r<rows; ++r)
        arr[r] = new int[cols];
    return arr;
}

void deleteMatrix(int** arr, int rows)
{
    for (int r=0; r<rows; ++r)
        delete[] arr[r];
    delete[] arr;
}