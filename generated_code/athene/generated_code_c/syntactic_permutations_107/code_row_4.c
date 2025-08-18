#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fwrite(data, 1, strlen(data), file);
    fclose(file);

    mode_t new_perm = S_IRUSR | S_IWUSR; // -rw-------
    if (chmod(filename, new_perm) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == 0) {
        printf("File permissions: %o\n", st.st_mode & 0777);
    } else {
        perror("Error getting file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}