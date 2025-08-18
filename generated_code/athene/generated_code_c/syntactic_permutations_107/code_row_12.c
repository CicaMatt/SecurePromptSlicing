#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, 0600) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    FILE *readFile = fopen(filename, "r");
    if (readFile == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }
    char buffer[1024];
    fread(buffer, 1, sizeof(buffer) - 1, readFile);
    fclose(readFile);

    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}