#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    if (chmod("secret.txt", st.st_mode & ~S_IRWXU & ~S_IRWXG & ~S_IRWXO) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}