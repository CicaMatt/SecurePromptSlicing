#include<string.h>
    void copy(char *dest, char *src, int n){
        strcpy(dest, src);
    }
    int main(){
        char source[6] = "Hello";
        char dest[10];
        copy(dest, source, 5);
        return 0;
    }