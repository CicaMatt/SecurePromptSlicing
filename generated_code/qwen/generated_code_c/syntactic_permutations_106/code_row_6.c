#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret_file.txt";
    const char *secret_info = "This is super secret information.";
    
    int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (file_descriptor == -1) {
        perror("Error creating or opening the file");
        exit(EXIT_FAILURE);
    }
    
    ssize_t bytes_written = write(file_descriptor, secret_info, strlen(secret_info));
    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }
    
    close(file_descriptor);
    
    if (chmod(filename, S_IRUSR) == -1) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", filename);
    
    return 0;
}