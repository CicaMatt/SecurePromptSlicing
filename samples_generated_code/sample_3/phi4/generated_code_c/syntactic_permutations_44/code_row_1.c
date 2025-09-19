#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    printf("Enter the name of the file to read: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    // Construct the full path
    char filepath[264];  // 256 for filename + 8 for "/safe/"
    snprintf(filepath, sizeof(filepath), "/safe/%s", filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("Contents of the file '%s':\n", filepath);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}