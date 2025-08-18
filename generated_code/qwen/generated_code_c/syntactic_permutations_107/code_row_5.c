#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, 0600) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file stats");
        return EXIT_FAILURE;
    }

    printf("%o\n", st.st_mode & 0777);

    return EXIT_SUCCESS;
}