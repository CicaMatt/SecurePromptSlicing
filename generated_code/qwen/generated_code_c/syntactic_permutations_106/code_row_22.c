#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(fd, secret_info, strlen(secret_info));
    if (bytes_written != strlen(secret_info)) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    if (chmod(filename, 0444) == -1) {
        perror("Error changing permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}