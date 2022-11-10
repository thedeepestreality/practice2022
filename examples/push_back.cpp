#include <iostream>

void push_back(int*& ar, size_t sz, int val){
    int* tmp = new int[sz+1];
    for (size_t idx = 0; idx < sz; ++idx)
        tmp[idx] = ar[idx];
    tmp[sz] = val;
    delete[] ar;
    ar = tmp;
}

int main(){
    char str[16];
    std::cin.getline(str, 16, ';');
    // std::cin.get(str, 16);
    std::cout << "str = " << str << '\n';
    // int n = 3;
    // int* arr = new int[n];
    // arr[0] = arr[1] = arr[2] = 0;
    // push_back(arr, n, 2);
    // delete[] arr;
    return 0;
}