#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *filename = "secret_info.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "Super Secret Info");
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    return EXIT_SUCCESS;
}