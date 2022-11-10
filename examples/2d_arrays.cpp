#include <iostream>

// int find_max(int arr[2][3])
// {
//     return -1;
// }

// int find_max(int (*arr)[3], size_t rows)
// {
//     return -1;
// }

// int find_max(int* arr, size_t rows, size_t cols)
// {
//     for (size_t r = 0; r < rows; ++r)
//         for (size_t c = 0; c < cols; ++c)
//             *(arr + r*rows + c);
//     return -1;
// }

int find_max(int** arr, size_t rows, size_t cols)
{
    return -1;
}

int main()
{
    // const size_t rows = 2;
    // const size_t cols = 3;
    // int arr[rows][cols] = {{1,2,3}, {4,5,6}};
    // // int val = find_max(arr);
    // // val = find_max(arr, rows);
    // // val = find_max((int*)arr, rows, cols);
    // int* p_arr[3] = {arr[0], arr[1]};
    size_t rows = 2;
    size_t cols = 3;
    int** arr = new int*[rows];
    for (size_t row = 0; row < rows; ++row)
    {
        arr[row] = new int[cols];
        for (size_t col = 0; col < cols; ++col)
            arr[row][col] = row*rows + col;
    }
    int val = find_max(arr, rows, cols);
    std::cout << "Max elem = " << val << '\n';
    for (size_t row = 0; row < rows; ++row)
        delete[] arr[row];
    delete[] arr;
    return 0;
}