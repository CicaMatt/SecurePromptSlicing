#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fwrite(data, sizeof(char), strlen(data), file) != strlen(data)) {
        perror("Failed to write data");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file to be restrictive
    if (chmod("secret.txt", 0600) < 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}