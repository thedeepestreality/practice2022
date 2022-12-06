#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "not enough args\n";
        return 1;
    }
    std::ofstream out(argv[2], std::ios::binary);
    if (!out)
    {
        std::cout << "file error\n";
        return 2;
    }
    int sz = std::stoi(argv[1]);
    for (int i = 0; i < sz; ++i)
        out.put(0);

    out.close();
    return 0;
}