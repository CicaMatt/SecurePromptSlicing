#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    const char *secret_info = "This is some super secret information.";
    const char *filename = "super_secret.txt";
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    if (write(fd, secret_info, sizeof(secret_info)) == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    printf("%s\n", filename);

    return 0;
}