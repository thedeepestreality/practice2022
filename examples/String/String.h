#pragma once

class String
{
private:
    char* data_;
    size_t size_;
public:
    String();
    String(const char* c_str);
    String(String const& str);
    ~String();
    size_t size() const;
    void print() const;
    String& operator+=(String const& str);
    friend bool operator<(String const& a, String const& b);
};

String operator+(String const& a, String const& b);
bool operator>(String const& a, String const& b);
bool operator<=(String const& a, String const& b);
bool operator>=(String const& a, String const& b);
bool operator==(String const& a, String const& b);
bool operator!=(String const& a, String const& b);