#include <iostream>

int main()
{
    std::cout << "Input rows: ";
    int rows;
    std::cin >> rows;
    std::cout << "Input cols: ";
    int cols;
    std::cin >> cols;
    //fill the matrix and transpose it
    int** source = new int*[rows];
    for (int i=0; i<rows; ++i){
        source[i] = new int[cols];
        for (int j=0; j<cols; ++j){
            source[i][j] = i*cols + j + 1;
            std::cout << source[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    int** transposed = new int*[cols];
    for (int i=0; i<cols; ++i){
        transposed[i] = new int[rows];
        for (int j=0; j<rows; ++j){
            transposed[i][j] = source[j][i];
            std::cout << transposed[i][j] << ' ';
        }
        std::cout << '\n';
    }

    //free the memory
    for (int i=0; i<cols; ++i)
        delete[] transposed[i];
    for (int i=0; i<rows; ++i)
        delete[] source[i];
    delete[] transposed;
    delete[] source;

    return 0;
}