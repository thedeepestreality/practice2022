#include <iostream>
#include "utils.h"



int main()
{
    const int cRows = 3;
    const int cCols = 4;
    int** arr = createMatrix(cRows, cCols);
    arr[0][0] = 1;
    //...some code...
    deleteMatrix(arr, cRows);
    return 0;
}