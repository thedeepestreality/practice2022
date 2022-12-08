#include <iostream>

enum class DayOfWeek {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

void printDayOfWeek(DayOfWeek day)
{
    switch(day){
        case DayOfWeek::Monday:
            std::cout << "Monday" << std::endl;
            break;
        case DayOfWeek::Tuesday:
            std::cout << "Tuesday" << std::endl;
            break;
    }
}

enum ImgTypes{
    Rgb = 5,
    Gs = 1,
    Bin = 3
};  

struct Image{
    size_t width;
    size_t height;
    unsigned char* data;
    ImgTypes type;
};

union ParamVal{
    char char_val;
    int int_val;
    double double_val;
};

enum class ParamType{
    Char,
    Int,
    Double
};

struct Parameter{
    ParamVal val;
    ParamType type;
};

enum class Dir{
    Right,
    Bottom
};

struct Chad{
    long long int_val;
    double real_val;
};

union Virgin{
    long long int_val;
    double real_val;
};

union Party{
    char c;
    short s;
    int i;
    double d;
    int x[2];
};

struct Deconstructor{
    char bytes[4];
};

struct Desintegrator{
    char b1:1;
    char b2:1;
    char b3:1;
    char b4:1;
    char b5:1;
    char b6:1;
    char b7:1;
    char b8:1;
};

struct Dummy{
    char index:6;
};

int main()
{
    long long victim = 5;
    *(double*)&victim = 3.14;
    std::cout << victim << std::endl;
    Virgin a;
    a.int_val = 4;
    a.real_val = 3.14;
    std::cout << sizeof(DayOfWeek) << std::endl;
    printDayOfWeek(DayOfWeek::Monday);

    union {
        int32_t val;
        char arr[4];
    };

    val = 257;
    arr[0] = 2;

    // Deconstructor megatron9000 = *(Deconstructor*)&val;
    // std::cout << megatron9000.bytes[1] << std::endl;

    Deconstructor d1 = {"123"};
    Deconstructor d2 = d1;

    char c = 2;
    Disintegrator di = *(Disintegrator*)&c;
    std::cout << di.b1 << std::endl;

    return 0;
}