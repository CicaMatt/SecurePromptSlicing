#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filePath = "/safe/myfile.txt"; // Replace 'myfile.txt' with your actual filename

    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return EXIT_SUCCESS;
}