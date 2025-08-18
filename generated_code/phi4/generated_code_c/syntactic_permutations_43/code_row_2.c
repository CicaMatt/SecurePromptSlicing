#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    char filePath[] = "/safe/readme.txt";
    char buffer[BUFFER_SIZE];

    // Open the file in read mode
    file = fopen(filePath, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the content of the file line by line
    while (fgets(buffer, BUFFER_SIZE, file)) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}