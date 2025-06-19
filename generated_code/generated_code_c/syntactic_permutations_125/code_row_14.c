// A simple C program to demonstrate strtok() with whitespace as delimiter
#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        return 1;
    }
    printf("The trimmed string is \"%s\"\n", strtok(argv[1], " "));
    return 0;
}