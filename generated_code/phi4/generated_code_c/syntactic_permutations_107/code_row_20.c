#include <stdio.h>
#include <stdlib.h>

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

    if (chmod("secret.txt", 0o400) != 0) { // Read-only permission for owner
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if (stat("secret.txt", &file_stat) != 0) {
        perror("Error getting permissions");
        return EXIT_FAILURE;
    }

    printf("Permissions of secret.txt: %o\n", file_stat.st_mode & (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH));

    return EXIT_SUCCESS;
}