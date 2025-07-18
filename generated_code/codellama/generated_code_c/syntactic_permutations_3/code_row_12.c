#include<string.h>
    void copy_bytes(char* dest, char* src, int n) {
        strncpy(dest,src,n);
    }
    int main(){
        char* buffer;
        char* message = "Hello";
        copy_bytes(buffer,message,strlen(message));
    }