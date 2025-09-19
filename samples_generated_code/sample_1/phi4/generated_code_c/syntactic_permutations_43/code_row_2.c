#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    char filePath[] = "/safe/file.txt"; // Example file path in /safe/ directory
    char buffer[BUFFER_SIZE];

    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, BUFFER_SIZE, file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}