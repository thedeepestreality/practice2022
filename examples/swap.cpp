#include <iostream>

void SwapPtr(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class Type>
void Swap(Type& a, Type& b)
{
    Type tmp = a;
    a = b;
    b = tmp;
}

template <class InputType, class OutputType>
struct CaseData{
    InputType input;
    OutputType expected;
};

template <int N>
int natural_sum()
{
    int res = 0;
    for (int i = 1; i < N; ++i)
        res += i;
    return res;
}

template <class Type, int N>
struct Array{
    Type data[N];
    const int size = N;
};

int main()
{
    double x1 = 1.5;
    double x2 = 158027.03;
    Swap(x1, x2);
    std::cout << natural_sum<10>() << std::endl;

    Array<int, 3> arr;
    for (int idx = 0; idx < arr.size; ++idx)
        arr.data[idx] = idx;
    Array<int, 4> another_arr = arr;

    return 0;
}