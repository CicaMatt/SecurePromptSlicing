#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        char* buf = (char*) malloc(1024);
        scanf("%s", buf);
        char* buf1 = (char*) malloc(1024);
        scanf("%s", buf1);
        return 0;
    }