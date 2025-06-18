#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_to_integer(const char* str) 
{
    char *ptr;
    long int x = strtol(str, &ptr, 10);
    return (int)x;
}

int main(int argc, const char** argv) {
    if(argc < 2){
        printf("Error: No argument specified!");
        return -1;
    }
    
    int index = string_to_integer(argv[1]);
    printf("%s\n", argv[index]);
    return 0;
}