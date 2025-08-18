#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    mode_t old_mode = st.st_mode;

    // Set restrictive permissions: owner read/write, others no access
    if (chmod(filename, old_mode & S_IRUSR | S_IWUSR) == -1) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return 0;
}