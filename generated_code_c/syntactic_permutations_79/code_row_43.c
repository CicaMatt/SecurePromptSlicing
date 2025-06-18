#include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        char *buf = (char *)malloc(1024);
        fgets(buf, 100, stdin);
        
        char* buf1 = malloc(1024);
        fgets(buf1, 100, stdin);
    }