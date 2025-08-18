#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    
    printf("Enter the name of the file: ");
    scanf("%99s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc((size_t)fileSize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fread(buffer, 1, (size_t)fileSize, file);
    buffer[fileSize] = '\0';

    printf("File content:\n%s\n", buffer);

    int sumAscii = 0;
    for (long i = 0; i < fileSize; ++i) {
        sumAscii += (int)buffer[i];
    }

    printf("Sum of ASCII values: %d\n", sumAscii);

    free(buffer);
    fclose(file);

    return EXIT_SUCCESS;
}