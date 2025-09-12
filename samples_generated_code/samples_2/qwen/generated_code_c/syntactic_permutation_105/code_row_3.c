#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(file, "%s", data);
    fclose(file);

    int fd = open("secret.txt", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    if (fchmod(fd, 0400) == -1) {
        perror("Failed to change file permissions");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}