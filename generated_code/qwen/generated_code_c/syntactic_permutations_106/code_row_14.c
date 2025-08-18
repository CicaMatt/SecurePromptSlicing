#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }

    fwrite(secret_info, strlen(secret_info), 1, file);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}