#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, 0400) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}