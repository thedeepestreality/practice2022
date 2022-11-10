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

int& find_max(int** arr, size_t rows, size_t cols){
    size_t r_max = 0;
    size_t c_max = 0;
    for (size_t row = 0; row < rows; ++row)
        for (size_t col = 0; col < cols; ++col)
            if (arr[row][col] > arr[r_max][c_max]){
                r_max = row;
                c_max = col;
            }
    return arr[r_max][c_max];
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
            arr[row][col] = row*cols + col;
    }
    int& val = find_max(arr, rows, cols);
    std::cout << "Max elem = " << val << '\n';
    val = 0;
    std::cout << "Max elem = " << arr[1][2] << '\n';
    for (size_t row = 0; row < rows; ++row)
        delete[] arr[row];
    delete[] arr;

    double d_val = 1.5;
    long long l_val = static_cast<long long>(d_val);
    //l_val = *(long long*)&d_val;
    // l_val = reinterpret_cast<long long>(d_val);
    l_val = (long long)d_val;
    long long& r_val = reinterpret_cast<long long&>(d_val);
    std::cout << "d_val = " << d_val << '\n';
    std::cout << "l_val = " << l_val << '\n';
    std::cout << "r_val = " << r_val << '\n';

    int val1 = 3;
    int& rval = val1;
    rval = 4;
    const int& cval = val1;
    int& hackerman = const_cast<int&>(cval);

    return 0;
}