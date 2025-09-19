#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void save_file(const char *file_data, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(file_data);
    ssize_t bytes_written = write(fd, file_data, len);
    if (bytes_written != len) {
        perror("Error writing to file");
        close(fd);
        unlink(path); // Remove partially written file
        exit(EXIT_FAILURE);
    }
    
    close(fd);
}

int main() {
    // Simulate receiving a PDF file as a string of bytes
    const char *pdf_data = "PDF binary data here..."; // Replace with actual PDF content
    const char *filename = "example.pdf";

    // Ensure the uploads directory exists
    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Error creating uploads directory");
        exit(EXIT_FAILURE);
    }

    save_file(pdf_data, filename);

    printf("File saved successfully.\n");

    return 0;
}