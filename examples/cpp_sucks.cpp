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

    //gather several char into one integer variable
    char ch_arr[] = {2, 1,0,0};
    int val = *(int*)ch_arr;
    printf("%d\n", val);
    return 0;
}