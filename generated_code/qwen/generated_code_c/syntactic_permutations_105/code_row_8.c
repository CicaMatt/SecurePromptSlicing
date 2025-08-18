#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}