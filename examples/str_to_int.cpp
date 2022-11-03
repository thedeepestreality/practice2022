#include <iostream>
#include <cstring>

int str2int(char* str){
    size_t sz = strlen(str);
    int res = 0;
    int deg = 1;
    for (int idx = sz-1; idx >= 0; --idx){
        int digit = str[idx] - 48;
        res += digit*deg;
        deg *= 10;
    }
    return res;
}
int main(){
    int val = str2int("123");
    std::cout << val;
    return 0;
}