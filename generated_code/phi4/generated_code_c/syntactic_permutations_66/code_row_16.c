#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 260

int save_pdf(const char *pdf_content, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return -1;
    }

    size_t written_bytes = fwrite(pdf_content, 1, strlen(pdf_content), file);

    if (written_bytes < strlen(pdf_content)) {
        fprintf(stderr, "Error writing to file: %s\n", filename);
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pdf_content> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pdf_content = argv[1];
    const char *filename = argv[2];

    // Ensure the filename ends with .pdf
    size_t len = strlen(filename);
    if (len >= 4 && strcmp(filename + len - 4, ".pdf") != 0) {
        char new_filename[MAX_PATH_LENGTH];
        snprintf(new_filename, sizeof(new_filename), "%s.pdf", filename);

        // Save the file with a .pdf extension
        if (save_pdf(pdf_content, new_filename) == 0) {
            printf("PDF saved as %s\n", new_filename);
        } else {
            return EXIT_FAILURE;
        }
    } else {
        // Directly save the PDF content to the provided filename
        if (save_pdf(pdf_content, filename) == 0) {
            printf("PDF saved as %s\n", filename);
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


This C program assumes that the `pdf_content` is passed as a string representing binary data of a PDF file. It saves this content to a file with an appropriate `.pdf` extension in the current directory. The program takes two command-line arguments: the content of the PDF and the desired filename. If the provided filename does not end with `.pdf`, it appends `.pdf` to the name before saving.