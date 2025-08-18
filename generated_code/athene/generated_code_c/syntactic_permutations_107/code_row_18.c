#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
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

    FILE *printFile = fopen(filename, "r");
    if (printFile == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), printFile)) {
        printf("%s", buffer);
    }
    fclose(printFile);

    return 0;
}