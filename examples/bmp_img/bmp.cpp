#include <iostream>
#include <fstream>

int main(){
    std::ifstream in("Lenna2.bmp", std::ios::binary);
    if (!in){
        std::cout << "failed to open file" << std::endl;
        return 1;
    }
    unsigned char buf[64];
    //READING BITMAPFILEHEADER
    in.read((char*)buf, 2);
    std::cout << "First two bytes: \n";
    std::cout << (char)buf[0] << (char)buf[1] << std::endl;

    int32_t file_sz;
    in.read((char*)&file_sz, 4);
    std::cout << "File size: " << file_sz << std::endl;
    in.seekg(4, std::ios::cur);

    int32_t offset;
    in.read((char*)&offset, 4);
    std::cout << "offset: " << offset << std::endl;

    //READING BITMAPINFOHEADER
    in.seekg(4, std::ios::cur);
    int32_t width;
    int32_t height;
    in.read((char*)&width, 4);
    in.read((char*)&height, 4);
    std::cout << "size: " << width << ' ' << height << std::endl;
    in.seekg(2, std::ios::cur);
    int16_t depth;
    in.read((char*)&depth, 2);
    std::cout << "depth: " << depth << std::endl;
    in.seekg(4, std::ios::cur);
    int32_t img_size;
    in.read((char*)&img_size, 4);
    std::cout << "img size: " << img_size << std::endl;
    
    in.seekg(16, std::ios::cur);
    in.read((char*)buf, 3);
    //img[0][0] - B G R - 57 22 82
    std::cout << "BGR[511][0]: " << (int)buf[0] << ' ';
    std::cout << (int)buf[1] << ' ';
    std::cout << (int)buf[2] << std::endl;

    in.read((char*)buf, 3);
    std::cout << "BGR[511][1]: " << (int)buf[0] << ' ';
    std::cout << (int)buf[1] << ' ';
    std::cout << (int)buf[2] << std::endl;

    in.read((char*)buf, 3);
    std::cout << "BGR[511][2]: " << (int)buf[0] << ' ';
    std::cout << (int)buf[1] << ' ';
    std::cout << (int)buf[2] << std::endl;

    in.close();
    return 0;
}