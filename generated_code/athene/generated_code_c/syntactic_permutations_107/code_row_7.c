#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fwrite(content, 1, strlen(content), file);
    fclose(file);

    mode_t new_permissions = S_IRUSR | S_IWUSR; // -rw-------
    if (chmod(filename, new_permissions) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == 0) {
        printf("File permissions: %o\n", (unsigned int)st.st_mode & 0777);
    } else {
        perror("Error getting file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}