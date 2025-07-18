#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        char *buffer_a = (char *)malloc(sizeof(char) * 1024);
        char *buffer_b = (char *)malloc(sizeof(char) * 1024);
    
        fgets(buffer_a, 1024, stdin);
        fgets(buffer_b, 1024, stdin);
    }