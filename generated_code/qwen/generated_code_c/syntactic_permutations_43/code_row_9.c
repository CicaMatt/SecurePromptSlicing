#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char ch;

    // Open file in read mode
    file = fopen("example.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read characters from file until end of file is reached
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}