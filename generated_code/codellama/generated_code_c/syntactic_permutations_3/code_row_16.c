#include<stdio.h>
#include <stdlib.h>

void copy_bytes(char* dst, int numBytes) {
    char *src = "Hello";
    for (int i = 0; i < numBytes; ++i) {
        *dst++ = *src++;
    }
}

int main()
{
    char buffer[6]={' ',' ',' ',' ',' ','\0'};
    copy_bytes(buffer,5);
    printf("%s",buffer);
    return 0;
}