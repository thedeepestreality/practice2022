#include <iostream>
#include <fstream>

struct ImgInfo{
    int width;
    int height;
    int channels;
};

#pragma pack(push,1)
struct Dummy{
    int x;
    char y;
};
#pragma pack(pop)

int main(){

    std::cout << sizeof(Dummy) << std::endl;
    // ImgInfo img;
    // img.width = 640;
    // img.height = 480;
    // img.channels = 3;
    // std::ofstream bmp("out.dat", std::ios::binary);
    // if (!bmp){
    //     std::cout << "error\n";
    //     return 1;
    // }
    // bmp.write((char*)&img, sizeof(img));
    // bmp.close();

    // ImgInfo bmp_in;

    // std::ifstream bmp_in_file("out.dat", std::ios::binary);
    // if (!bmp_in_file){
    //     std::cout << "error\n";
    //     return 1;
    // }
    // bmp_in_file.read((char*)&bmp_in, sizeof(bmp_in));
    // bmp_in_file.close();

    // std::cout << bmp_in.height << std::endl;

    

    return 0;
}