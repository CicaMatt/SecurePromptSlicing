#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    size_t len = sizeof(data) - 1;

    if (fwrite(data, 1, len, file) != len) {
        perror("Failed to write data");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change permissions to be restrictive
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}