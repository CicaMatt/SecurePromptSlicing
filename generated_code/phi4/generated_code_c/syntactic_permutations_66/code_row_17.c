#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void save_pdf(const char *filename) {
    FILE *input = fopen(filename, "rb");
    if (input == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Extract filename without extension
    char base_filename[BUFFER_SIZE];
    strncpy(base_filename, filename, strlen(filename));
    char *last_dot = strrchr(base_filename, '.');
    if (last_dot != NULL) {
        *last_dot = '\0';
    }

    char output_path[2*BUFFER_SIZE] = "./";
    strcat(output_path, base_filename);
    strcat(output_path, ".pdf");

    FILE *output = fopen(output_path, "wb");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);

    printf("PDF saved as %s\n", output_path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    save_pdf(argv[1]);

    return EXIT_SUCCESS;
}