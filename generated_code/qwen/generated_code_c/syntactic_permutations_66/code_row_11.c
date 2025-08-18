#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];

    printf("Enter the name of the PDF file to open: ");
    scanf("%s", filename);

    if (filename == NULL) {
        fprintf(stderr, "No filename provided.\n");
        return EXIT_FAILURE;
    }

    // Append .pdf extension if not already present
    char *ext = ".pdf";
    int len = strlen(filename);
    if (len < 4 || strcmp(&filename[len-4], ext) != 0) {
        strcat(filename, ext);
    }

    file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open the file");
        return EXIT_FAILURE;
    }

    printf("File opened successfully.\n");

    // Simulate processing of the PDF file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}