#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "/safe/example.txt";
    char ch;

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the content of the file character by character
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}