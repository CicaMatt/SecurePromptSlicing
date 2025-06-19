#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_SIZE 4096
int main(void) {
    char* env = getenv("REQUEST_METHOD");
    if (strncmp(env, "GET", 3) == 0){
        printf("HTTP/1.1 200 OK\n");
    }else{
        printf("HTTP/1.1 405 METHOD NOT ALLOWED\n");
    }
    return 0;
}