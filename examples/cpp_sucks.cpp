#include <stdio.h>

double m[]={7709179928849219.0,771};

int main(){
    //C++Sucks
    while (m[1]--)
        m[0]*=2;
    printf((char*)m);

    //divide integer variable to separate bytes
    int x = 257;
    char* x_str = (char*) &x;
    printf("%d %d %d %d\n",x_str[0], x_str[1], x_str[2], x_str[3]);
    char c = 42;
    char b03 = (c<<4) >> 4;
    b03 = c & 0x0F;
    char b47 = c >> 4;

    char x03 = (x<<28)>>28;
    x03 = x & 0x0F;

    char c1 = 42;
    char c2 = 24;
    char b0 = c1 & 0x3F;
    char b1 = (c1 >> 6) | ((c2 & 0xF) << 2);

    // step array
    int** matr = new int*[3];
    matr[0] = new int[5];
    matr[1] = new int[10];
    matr[2] = new int[2];

    //gather several char into one integer variable
    char ch_arr[] = {2, 1,0,0};
    int val = *(int*)ch_arr;
    printf("%d\n", val);
    return 0;
}