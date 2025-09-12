#include <stdio.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}