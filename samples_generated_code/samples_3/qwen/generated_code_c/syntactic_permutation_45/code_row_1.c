#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *filename = "requested_file.txt"; // Change this to your file name
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}