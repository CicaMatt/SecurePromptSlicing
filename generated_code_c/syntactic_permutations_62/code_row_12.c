#include <stdio.h>  //printf, fopen, fread
#include <stdlib.h> //malloc, free, exit
#include <string.h> //memset, memcpy

int main() {
    char *buffer;
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        printf("Could not open file!\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char *)malloc(length + 1);
    if (!buffer) {
        printf("Could not allocate memory!\n");
        return 2;
    }
    fread(buffer, sizeof(char), length, file);
    memset(&buffer[length], '\0', 1);
    fclose(file);
    // Do stuff with the buffer
    free(buffer);
    return 0;
}