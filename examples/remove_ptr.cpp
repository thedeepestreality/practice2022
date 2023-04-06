#include <iostream>

template<class T>
bool is_pointer(T a){
    return false;
}

template<class T>
bool is_pointer(T* a){
    return true;
}

struct TypeKeeper{
    using IntType = int;
};

template<class T>
struct remove_ptr{
    using type = T;
};

template<class T>
struct remove_ptr<T*>{
    using type = typename remove_ptr<T>::type;
};

template<class T>
using remove_ptr_t = typename remove_ptr<T>::type;

template<class T>
void foo(T a)
{
    T b;
    //typename remove_ptr<T>::type x;
    remove_ptr_t<T> x;
    // if (is_pointer(a))
    //     std::cout << "a is pointer type\n";
    // else
    //     std::cout << "a is not pointer type\n";
}

// T* -> T
// T  -> T

int main()
{
    int x = 1;
    int const& crx = x;
    int& rx = const_cast<int&>(crx);
    rx = 2;

    TypeKeeper::IntType xx;

    int* x_ptr = &x;
    foo(x_ptr);

    return 0;
}