#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads/"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    char output_filename[BUFFER_SIZE];
    snprintf(output_filename, sizeof(output_filename), "%s%s", UPLOAD_DIR, basename(input_filename));

    if (access(UPLOAD_DIR, F_OK) != 0) {
        mkdir(UPLOAD_DIR, 0755);
    }

    int in_fd = open(input_filename, O_RDONLY);
    if (in_fd == -1) {
        perror("Error opening input file");
        return 1;
    }

    int out_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd == -1) {
        perror("Error creating output file");
        close(in_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t nread;

    while ((nread = read(in_fd, buffer, sizeof(buffer))) > 0) {
        if (write(out_fd, buffer, nread) != nread) {
            perror("Error writing to output file");
            close(in_fd);
            close(out_fd);
            return 1;
        }
    }

    if (nread == -1) {
        perror("Error reading from input file");
        close(in_fd);
        close(out_fd);
        return 1;
    }

    close(in_fd);
    close(out_fd);

    printf("File %s saved to %s\n", input_filename, output_filename);
    return 0;
}