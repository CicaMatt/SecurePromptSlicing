#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/input.txt";
    char ch;

    // Open the file in read mode
    file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print each character from the file until EOF is reached
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}