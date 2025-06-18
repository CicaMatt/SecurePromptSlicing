#include <stdio.h>
    #include <stdlib.h>
    
    void main()
    {
        char *buf = (char*)malloc(sizeof(char)*1024);
        fgets(buf, 1024, stdin);
        //copying input from stdin to buf
        char *buf1 = (char*)malloc(sizeof(char)*1024);
        fgets(buf1, 1024, stdin);
    }