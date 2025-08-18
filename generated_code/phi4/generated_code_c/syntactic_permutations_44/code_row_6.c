#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[256];
    
    printf("Enter the name of the file to read: ");
    scanf("%255s", filename);

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print contents of the file
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

    return 0;
}