#include <stdio.h>
    #include <string.h>
    
    int main(int argc, char *argv[]){
        char* str=argv[1];
        char* index=argv[2];
        printf("%s",str[atoi(index)]);
        return 0;
    }