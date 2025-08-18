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
    if (fputs(content, file) == EOF) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);
    
    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    // Change the permissions of the file to restrictive: owner can read and write, no other permissions
    if (chmod("secret.txt", st.st_mode & ~(S_IRWXG | S_IRWXO)) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}