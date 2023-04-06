#include <iostream>

template <class Type>
class Vector{
    Type* m_data;
    size_t m_size;
    size_t m_capacity;
public:
    Vector() {}
    Vector(size_t sz){
        m_capacity = m_size = sz;
        m_data = new Type[m_size];
    }
    ~Vector() { delete[] m_data; }
    Type& operator[](int idx){
        return m_data[idx];
    }
};

template<>
class Vector<bool>{
    unsigned char* m_data;
    size_t m_size;
    size_t m_capacity;
    size_t m_bit_size;
public:
    Vector() {}
    Vector(size_t size){
        m_capacity = m_size = size/8 + 1;
        m_data = new unsigned char[m_size];
        m_bit_size = size;
    }
    ~Vector() { delete[] m_data; }
    void push_back(bool val){
        size_t idx = m_bit_size/8;
        if (val)
            m_data[idx] |= (1 << m_bit_size%8 );
        else
            m_data[idx] &= ~(1 << m_bit_size%8 );
    }

    class VecProxy;

    VecProxy operator[](int idx){
        return VecProxy(m_data, idx);
    }

    class VecProxy{
        unsigned char* m_data;
        size_t m_bit_idx;
    public:
        VecProxy(unsigned char* data, size_t bit_idx) : m_data(data), m_bit_idx(bit_idx) {}
        VecProxy& operator=(bool val){
            size_t byte_idx = m_bit_idx/8;
            size_t bit_idx = m_bit_idx % 8;
            if (val)
                m_data[byte_idx] |= (1 << bit_idx );
            else
                m_data[byte_idx] &= ~(1 <<bit_idx );
            return *this;
        }
        operator bool(){
            size_t idx = m_bit_idx/8;
            size_t bit_idx = m_bit_idx % 8;
            return (m_data[idx] >> bit_idx) & 0x01;
        }
    };
};

int main(){
    Vector<int> x(3);
    x[0] = -5;
    x[1] = 2; 
    x[2] = 0;

    Vector<bool> y(3);
    y[0] = 1;
    y[1] = 0;
    y[2] = 1;
    std::cout << y[0] << std::endl;
    return 0;
}