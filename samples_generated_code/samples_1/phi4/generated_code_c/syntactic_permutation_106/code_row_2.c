#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "super_secret.txt";
    const char *secret_info = "This is some super secret info.\n";

    // Create and write the secret information to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change the permissions of the file to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return 1;
    }

    // Print the name of the file to the screen
    printf("%s\n", filename);

    return 0;
}