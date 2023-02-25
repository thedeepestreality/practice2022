#include "String.h"
#include <cstring>
#include <iostream>

String::String() : size_(1), data_(new char[1])
{
    data_[0] = 0;
}

String::String(const char* c_str) : size_(strlen(c_str) + 1)
{
    data_ = new char[size_];
    for (size_t idx = 0; idx < size_; ++idx)
        data_[idx] = c_str[idx];
}

String::String(String const& str) : size_(str.size_)
{
    data_ = new char[size_];
    for (size_t idx = 0; idx < size_; ++idx)
        data_[idx] = str.data_[idx];
}

String::~String()
{
    delete[] data_;
}

size_t String::size() const
{
    return size_ - 1;
}

void String::print() const
{
    std::cout << data_ << '\n';
}

String& String::operator+=(String const& str)
{
    char* tmp = new char[size_ + str.size_ - 1];
    for (size_t idx = 0; idx < size_ - 1; ++idx)
        tmp[idx] = data_[idx];
    for (size_t idx = 0; idx < str.size_; ++idx)
        tmp[size_ + idx - 1] = str.data_[idx];
    size_ += str.size_ - 1;
    delete[] data_;
    data_ = tmp;
    return *this;
}

String operator+(String const& a, String const& b)
{
    String sum = a;
    sum += b;
    return sum;
}

bool operator<(String const& a, String const& b)
{
    return strcmp(a.data_, b.data_) < 0;
}
bool operator>(String const& a, String const& b)
{
    return b < a;
}

bool operator<=(String const& a, String const& b)
{
    return !(b < a);
}

bool operator>=(String const& a, String const& b)
{
    return !(a < b);
}

bool operator==(String const& a, String const& b)
{
    return !(a < b) && !(b < a);
}

bool operator!=(String const& a, String const& b)
{
    return (a < b) || (b < a);
}
