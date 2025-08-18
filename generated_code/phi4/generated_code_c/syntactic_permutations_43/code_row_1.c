#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char path[] = "/safe/somefile.txt";
    char buffer[256];

    // Open the file in read mode
    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print content of the file line by line
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}