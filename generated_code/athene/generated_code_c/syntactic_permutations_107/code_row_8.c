#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output_file";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fwrite(content, 1, strlen(content), file);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR)) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);

    return 0;
}