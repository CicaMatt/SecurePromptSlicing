#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }
    fputs(content, file);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);

    return EXIT_SUCCESS;
}