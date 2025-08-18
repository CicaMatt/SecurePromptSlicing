#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat(filename, &st) == 0) {
        printf("File permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    } else {
        perror("Failed to get file information");
        exit(EXIT_FAILURE);
    }

    return 0;
}