#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", data);
    fclose(file);

    int fd = open(filename, O_WRONLY);
    if (fd != -1) {
        fchmod(fd, S_IRUSR | S_IWUSR); // Change to restrictive permissions
        close(fd);
    }

    printf(".");

    return 0;
}