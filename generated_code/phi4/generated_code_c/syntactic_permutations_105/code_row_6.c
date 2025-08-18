#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        fclose(file);
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change permissions to be restrictive: only owner can read and write
    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    if (chmod("secret.txt", st.st_mode & ~(S_IRWXG | S_IRWXO)) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}