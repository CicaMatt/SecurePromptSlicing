#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(file, "%s", data);
    fclose(file);

    if (chmod("secret.txt", S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}