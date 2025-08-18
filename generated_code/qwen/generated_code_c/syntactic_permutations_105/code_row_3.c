#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, 0400) != 0) {
        perror("Error changing permissions");
        exit(EXIT_FAILURE);
    }

    return 0;
}