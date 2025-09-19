#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    if (fputs(content, file) == EOF) {
        fclose(file);
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    fclose(file);

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    mode_t new_mode = st.st_mode & ~S_IRWXG & ~S_IRWXO;
    if (chmod(filename, new_mode) == -1) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return 0;
}