#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fprintf(file, "%s", content) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file to restrictive
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}