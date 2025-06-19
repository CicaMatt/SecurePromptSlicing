#include <stdio.h>
#include <stdlib.h>
int main()
{
    // Allocate a buffer of 1024 bytes and store the address in buf.
    char *buf = (char *)malloc(sizeof(char) * 1024);

    // Read up to 100 characters from stdin into the allocated memory.
    fgets(buf, 100, stdin);

    // Allocate another buffer of 1024 bytes and store the address in buf1.
    char *buf1 = (char *)malloc(sizeof(char) * 1024);

    // Read up to 100 characters from stdin into the allocated memory.
    fgets(buf1, 100, stdin);
}