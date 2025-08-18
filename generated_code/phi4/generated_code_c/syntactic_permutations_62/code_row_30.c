#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file, *output;
    char filename[256], outputFilename[256];
    char buffer[1024];
    size_t bytesRead;

    printf("Enter the name of the input file: ");
    scanf("%255s", filename);

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    printf("Enter the name of the output file: ");
    scanf("%255s", outputFilename);

    output = fopen(outputFilename, "w");
    if (output == NULL) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(output, "%zu\n", bytesRead);

    fclose(output);

    if (bytesRead == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("Number of bytes read: %zu\n", bytesRead);
    }

    return EXIT_SUCCESS;
}