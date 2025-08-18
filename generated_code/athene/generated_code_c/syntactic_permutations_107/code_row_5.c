#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    size_t written = fwrite(content, 1, strlen(content), file);
    fclose(file);

    if (written != strlen(content)) {
        perror("fwrite");
        return EXIT_FAILURE;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("chmod");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);

    return EXIT_SUCCESS;
}