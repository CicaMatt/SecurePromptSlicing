#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", data);
    fclose(file);

    // Change the permissions of the file to restrictive (read/write for owner only)
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}