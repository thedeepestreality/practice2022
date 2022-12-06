#include <iostream>
#include <fstream>
#include <ctime>

int main()
{
    std::ifstream in("d1000.out", std::ios::binary);
    if (!in){
        std::cout << "file error!\n";
        return 1;
    }
    size_t counter = 0;
    const int BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    clock_t start = clock();
    in.seekg(0, std::ios_base::end);
    counter = in.tellg();
    in.seekg(0, std::ios_base::beg);
    // while(in.peek() != EOF){
    //     in.read(buf, BUF_SIZE);
    //     counter += in.gcount();
    // }
    clock_t fin = clock();
    std::cout << "elapsed: " << (double)(fin-start)/CLOCKS_PER_SEC << std::endl;

    std::cout << "File size is " << counter << std::endl;

    in.close();
    return 0;
}