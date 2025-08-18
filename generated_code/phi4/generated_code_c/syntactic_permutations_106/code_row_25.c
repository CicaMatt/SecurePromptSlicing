#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";

    // Create and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    fputs(secret_info, file);
    fclose(file);

    // Change permissions to read-only for owner
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, st.st_mode & ~S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the content of the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return EXIT_FAILURE;
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}