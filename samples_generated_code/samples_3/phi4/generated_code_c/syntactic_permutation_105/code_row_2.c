#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    struct stat st;
    if (stat("output.txt", &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Set the permissions to read and write for owner only
    if (chmod("output.txt", st.st_mode & ~S_IRWXG & ~S_IRWXO) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}