#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        perror("Failed to write data to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    mode_t permissions = st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    printf("Permissions: %o\n", permissions);

    if (chmod("secret.txt", S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get updated file status");
        return EXIT_FAILURE;
    }

    permissions = st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    printf("Updated Permissions: %o\n", permissions);

    return EXIT_SUCCESS;
}