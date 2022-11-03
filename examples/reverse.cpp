#include <iostream>

void fillArray(int* arr, size_t sz){
    for (size_t idx=0; idx < sz; ++idx)
        arr[idx] = idx;
}
void printArray(int* arr, size_t sz){
    for (size_t idx = 0; idx < sz; ++idx)
        std::cout << arr[idx] << ' ';
    std::cout << '\n';
}
void reverseArray(int* arr, size_t sz){
    for (size_t idx=0; idx < sz/2; ++idx){
        int tmp = arr[idx];
        arr[idx] = arr[sz - idx - 1];
        arr[sz - idx - 1] = tmp;
    }
}
int main(){
    size_t sz;
    std::cout << "Input size: ";
    std::cin >> sz;
    int* arr = new int[sz];
    fillArray(arr, sz);
    std::cout << "Initial array:\n";
    printArray(arr, sz);
    reverseArray(arr, sz);
    std::cout << "Reversed array:\n";
    printArray(arr, sz);
    delete[] arr;
    return 0;
}