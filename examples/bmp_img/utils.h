#ifndef _UTILS_H_
#define _UTILS_H_
//#pragma once
int** createMatrix(int rows, int cols);
void deleteMatrix(int** arr, int rows);

const int IMPORTANT_PARAM = 42;

void test_inline();

inline int sum(int a, int b){
    return a+b;
}
#endif