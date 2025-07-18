#include <stdio.h>
#include <string.h>
void memcpy(char* dst, char* src, int num){
    for (int i = 0; i < num; i++){
        *dst++ = *src++;
    }
}

int main(){
    char buffer[12] = {'\0'};
    char str[] = "Hello";
    memcpy(buffer, str, sizeof(str));
    printf("%s", buffer);
    return 0;
}