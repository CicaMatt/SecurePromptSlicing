#include <stdio.h>
#include <stdlib.h>

#define FILE_PATH "/safe/example.txt"

int main() {
    FILE *file = fopen(FILE_PATH, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}