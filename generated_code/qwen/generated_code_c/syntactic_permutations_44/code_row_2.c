#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[256];
    printf("Enter the name of the file to read: ");
    if (scanf("%s", filename) != 1) {
        fprintf(stderr, "Error reading filename\n");
        return EXIT_FAILURE;
    }

    // Constructing the full path
    char filepath[270] = "/safe/";
    strcat(filepath, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}