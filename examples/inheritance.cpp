#include <iostream>

class Base{
private:
    int x;
public:
    int y;
    Base() { std::cout << "Base constructor\n"; }
    Base(int _x) : x(_x) { std::cout << "Base param constructor\n"; }
    ~Base() {std::cout << "Base destructor\n"; }
protected:
    int z;
};

class Derived : public Base {
private:
    int dx;
public:
    int dy;
    Derived() : Base(1), dx(2) { 
        std::cout << "Derived constructor\n"; 
    }
    ~Derived() {std::cout << "Derived destructor\n"; }
protected:
    int dz;
};

class Grandparent : public Derived {
public:
    Grandparent() : Derived() {

    };
};

class Animal{
public:
    virtual void voice() const = 0;
    // virtual void voice() const {
    //     std::cout << "Undefined voice\n";
    // }
    void walk() {
        std::cout << "smth is walking\n";
    }
};

class Cat: public Animal {
public:
    void voice() const override {
        std::cout << "Meow\n";
    }

    void walk() {}
};

class Dog: public Animal {
public:
    void voice() const override {
        std::cout << "Bark!\n";
    }
};

class Chihuahua: public Dog {
public:
    void voice() const override {
        std::cout << "Scary maniac noise\n";
    }
};

void pullTail(Animal* a){
    Cat* c_ptr = dynamic_cast<Cat*>(a);
    if (c_ptr == nullptr)
        a->voice();
}

// NE LEZ' UB'YET!!!
// example of how NOT to do things
void foo(int const& x){
    int& rx = const_cast<int&>(x);
    rx = 5;
}

int main()
{
    Derived d;
    // Animal a;
    // a.voice();
    Cat c;
    c.voice();
    Animal* a_ptr = new Cat();
    a_ptr->voice();
    Cat* c_ptr = dynamic_cast<Cat*>(a_ptr);
    std::cout << "CAT PTR: " << c_ptr << "\n";
    delete a_ptr;
    Animal* ch = new Chihuahua();
    ch->voice();
    delete ch;

    Animal const& dog = Dog();
    dog.voice();

    int x = 52;
    foo(x);
    std::cout << "New x = " << x << "\n";

    return 0;
}