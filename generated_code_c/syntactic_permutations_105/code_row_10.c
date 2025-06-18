#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd = open("secret.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    char *msg = "This is a secret message\n";
    ssize_t nwrite = write(fd, msg, strlen(msg));
    if (nwrite == -1) {
        perror("Error writing to file");
        return EXIT_FAILURE;
    }
    close(fd);
    printf("Wrote %ld bytes to the file\n", nwrite);
    chmod("secret.txt", S_IRUSR | S_IWUSR);
}