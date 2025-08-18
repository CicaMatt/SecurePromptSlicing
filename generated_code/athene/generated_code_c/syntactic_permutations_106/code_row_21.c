#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *secret = "SuperSecretInfo";
    const char *filename = "secretfile.txt";

    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(fd, secret, strlen(secret));
    if (bytes_written == -1 || (size_t)bytes_written != strlen(secret)) {
        perror("Error writing to file");
        close(fd);
        unlink(filename);
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        unlink(filename);
        exit(EXIT_FAILURE);
    }

    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("Error changing permissions");
        unlink(filename);
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}