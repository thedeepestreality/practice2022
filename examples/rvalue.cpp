#include <iostream>

class Dummy{
    int* m_data = nullptr;
public:
    Dummy(){
        std::cout << "def\n";
    }

    Dummy(int x){
        std::cout << "param\n";
    }

    Dummy(Dummy const& val){
        std::cout << "copy\n";
    }

    Dummy(Dummy&& val){
        std::cout << "move\n";
        m_data = val.m_data;
        val.m_data = nullptr;
    }

    Dummy& operator=(Dummy const& val){
        std::cout << "copy op=\n";
        if (this == &val)
            return *this;
        return  *this;
    }

    Dummy& operator=(Dummy&& val){
        std::cout << "move op=\n";
        if (this == &val)
            return *this;
        std::swap(val.m_data, m_data);
        return *this;
    }

    ~Dummy(){
        std::cout << "dest\n";
    }
};

Dummy foo(){
    return Dummy();
}

Dummy bar(Dummy val){
    return val;
}

int main(){
    Dummy def; // def constructor
    Dummy param(5); // param constructor
    Dummy p = Dummy(5); // param constructor
    Dummy copy(p); // copy constructor
    Dummy c = Dummy(p); // copy constructor
    Dummy d; // def constructor
    d = Dummy(p); // copy constructor -> assignment move operator

    Dummy elisioned = foo(); // copy elision (prvalue) -- return optimization
    Dummy moved = std::move(d);
    std::cout << "------\n";
    Dummy test = bar(moved);
    std::cout << "------\n";
    int x = 1;
    //int& rx = 1;
    int const& cx = 1;
    //cx = 2;
    int&& rvx = 1;
    rvx = 2;

    return 0;
}