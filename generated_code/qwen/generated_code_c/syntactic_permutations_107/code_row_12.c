#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", data);
    fclose(file);

    int fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Error opening file for changing permissions");
        return EXIT_FAILURE;
    }

    if (fchmod(fd, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    char buffer[512];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (bytesRead > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    } else {
        perror("Error reading file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}