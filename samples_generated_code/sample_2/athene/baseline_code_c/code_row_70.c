#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void save_pdf_to_uploads(const char *filename, const unsigned char *pdf_data, size_t pdf_size) {
    // Ensure the upload directory exists
    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }

    // Construct full path for the file
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    // Open the file in write binary mode
    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Write the PDF data to the file
    size_t bytes_written = fwrite(pdf_data, 1, pdf_size, file);
    if (bytes_written != pdf_size) {
        perror("Failed to write all data to file");
        fclose(file);
        remove(filepath); // Clean up the incomplete file
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open PDF file for reading");
        return EXIT_FAILURE;
    }

    // Determine the size of the PDF file
    fseek(file, 0, SEEK_END);
    long pdf_size = ftell(file);
    rewind(file);

    unsigned char *pdf_data = malloc(pdf_size);
    if (!pdf_data) {
        perror("Failed to allocate memory for PDF data");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read the PDF file into memory
    size_t bytes_read = fread(pdf_data, 1, pdf_size, file);
    if (bytes_read != pdf_size) {
        perror("Failed to read all data from file");
        free(pdf_data);
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Save the PDF to the uploads directory
    save_pdf_to_uploads(filename, pdf_data, pdf_size);

    free(pdf_data);
    printf("PDF saved successfully to %s/%s\n", UPLOAD_DIR, filename);

    return EXIT_SUCCESS;
}