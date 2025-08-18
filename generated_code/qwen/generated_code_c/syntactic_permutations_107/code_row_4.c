#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);

    return EXIT_SUCCESS;
}