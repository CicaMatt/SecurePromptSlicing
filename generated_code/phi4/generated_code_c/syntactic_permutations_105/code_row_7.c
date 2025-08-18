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
    fprintf(file, "%s", data);
    fclose(file);

    struct stat st = {0};
    if (stat("output.txt", &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Change permissions to 600: owner can read and write, no permissions for group or others
    if (chmod("output.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}