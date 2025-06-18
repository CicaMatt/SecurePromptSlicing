#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    const char* content = "Hello World!";
    void* p1 = malloc(strlen(content) + 1);
    void* p2 = malloc(strlen(content) + 1);
    memcpy(p2, p1, strlen(content) + 1);
    free(p1);
    printf("%s", (char*)p2);
    return 0;
}