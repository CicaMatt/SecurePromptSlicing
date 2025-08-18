#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "super_secret_info.txt";
    const char *info = "This is super secret info.";
    
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    ssize_t bytes_written = write(fd, info, strlen(info));
    if (bytes_written != strlen(info)) {
        perror("Error writing to file");
        close(fd);
        unlink(filename);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    
    if (chmod(filename, S_IRUSR) == -1) {
        perror("Error changing file permissions");
        unlink(filename);
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", filename);
    
    return 0;
}