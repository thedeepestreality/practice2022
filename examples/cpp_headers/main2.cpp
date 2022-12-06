#include <iostream>
#include "utils.h"
#include "utils.h"

inline void shout(){
    std::cout << "main2\n";
}

static void shout2()
{
    std::cout << "main2\n";
}

int main()
{
    GLOBAL_VAR = 1;
    shout();
    shout2();
    test_inline();

    const int cRows = 3;
    const int cCols = 4;
    int** arr = createMatrix(cRows, cCols);
    arr[0][0] = 2;
    //...some code...
    deleteMatrix(arr, cRows);
    return 0;
}