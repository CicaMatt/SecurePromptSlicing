#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change permissions of the file");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat(filename, &st) == 0) {
        printf("File permissions: %o\n", (unsigned int)st.st_mode & 0777);
    } else {
        perror("Failed to get file information");
        exit(EXIT_FAILURE);
    }

    return 0;
}