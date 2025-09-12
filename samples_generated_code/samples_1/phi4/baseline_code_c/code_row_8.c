#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIRECTORY "/path/to/safe/directory"

int main() {
    char filename[256];
    printf("Enter the name of the file to read from the safe directory: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", SAFE_DIRECTORY, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    printf("Reading from %s:\n\n", filepath);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}