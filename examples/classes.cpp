#include <iostream>

//all fields are public
struct DynamicArrayInt
{
    size_t size;
    int* data;
};

void initArray(DynamicArrayInt& arr, size_t size)
{
    arr.size = size;
    arr.data = new int[arr.size];
}

//fill numbers from 0 to arr.size-1
void fillArray(DynamicArrayInt& arr)
{
    for (size_t idx = 0; idx < arr.size; ++idx)
        arr.data[idx] = idx;
}

void printArray(DynamicArrayInt& arr)
{
    for (size_t idx = 0; idx < arr.size; ++idx)
        std::cout << arr.data[idx] << std::endl;
}

void destroyArray(DynamicArrayInt& arr)
{
    delete[] arr.data;
}

class DynArrClass
{
private:
    size_t size_;
    int* data_;
public:
    //default constructor
    DynArrClass()
    {
        size_ = 10;
        data_ = new int[size_];
    }

    //constructor with parameter
    DynArrClass(size_t size)
    {
        size_ = size;
        data_ = new int[size_];
    }

    //destructor
    ~DynArrClass()
    {
        delete[] data_;
    }

    //object method
    size_t getSize()
    {
        return size_;
    }
};


int main()
{
    DynamicArrayInt dyn_arr;
    initArray(dyn_arr, 10);
    //this will break object consistency
    //which lead (potentially) to segfault
    //dyn_arr.size = 20;
    fillArray(dyn_arr);
    printArray(dyn_arr);
    destroyArray(dyn_arr);
    
    DynArrClass dyn_class(20);
    std::cout << "constructed: " << dyn_class.getSize() << std::endl;

    // constructors and destructors work wyth dynamic memory also
    DynArrClass* dyn_dyn_class = new DynArrClass(10);
    delete dyn_dyn_class;


    return 0;
}