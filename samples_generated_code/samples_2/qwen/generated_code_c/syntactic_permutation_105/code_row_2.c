#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, 0) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}