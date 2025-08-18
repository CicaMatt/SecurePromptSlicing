#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/input.txt";
    char buffer[256];

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the content of the file
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}