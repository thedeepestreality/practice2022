#include <vector>
#include <iostream>

struct Dummy{
    static int count;
    int m_val;
    Dummy(){
        std::cout << ++count << " Dummy!\n";
    }

    Dummy(int val) : m_val(val) {
        std::cout << ++count << " Dummy with val: " << val << "\n";
    }

    ~Dummy(){
        std::cout << --count << " Dummy died\n";
    }
};

int Dummy::count = 0;

int some_var;
void foo(){
    int some_var;
    ::some_var = 0;
}

int main(){
    std::vector<Dummy> vec(10);
    //vec.emplace_back();
    std::cout << "\n";
    //vec.push_back(Dummy());
    vec.emplace_back();
    std::cout << vec.capacity() << "\n";

    Dummy* d_arr = new Dummy[10];

    delete[] d_arr;

    Dummy* d_dyn = reinterpret_cast<Dummy*>(::operator new(10*sizeof(Dummy)));

    //placement new
    new(d_dyn) Dummy(100500);
    std::cout << (*reinterpret_cast<Dummy*>(d_dyn)).m_val << "\n";
    (*reinterpret_cast<Dummy*>(d_dyn)).~Dummy();
    ::operator delete[](d_dyn);
    std::cout << "before end\n";
    std::vector<Dummy> empty_vec();
    empty_vec.reserve(10);
    empty_vec.emplace_back(100500);
    return 0;
}