#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void save_pdf_file(const char *filename, const unsigned char *data, size_t data_size) {
    // Ensure the upload directory exists
    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Error creating uploads directory");
        exit(EXIT_FAILURE);
    }

    // Construct full path to save the file
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    // Open the file for writing
    int fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, data_size);
    if (bytes_written != data_size) {
        perror("Error writing to file");
        close(fd);
        unlink(filepath); // Remove partially written file
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);
}

int main() {
    const char *filename = "example.pdf";
    unsigned char sample_pdf_data[] = {0x25, 0x50, 0x44, 0x46}; // Example PDF header
    size_t data_size = sizeof(sample_pdf_data);

    save_pdf_file(filename, sample_pdf_data, data_size);
    printf("PDF file saved successfully.\n");

    return 0;
}