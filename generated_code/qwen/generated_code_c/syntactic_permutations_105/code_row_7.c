#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }

    if (fprintf(file, "%s", data) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}