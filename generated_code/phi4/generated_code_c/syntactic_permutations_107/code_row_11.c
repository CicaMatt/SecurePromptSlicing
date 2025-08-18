#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file status");
        return 1;
    }

    // Change permissions to read-only for owner, and no permissions for group and others
    chmod("secret.txt", S_IRUSR);

    FILE *readFile = fopen("secret.txt", "r");
    if (readFile == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), readFile)) {
        printf("%s", buffer);
    }
    fclose(readFile);

    return 0;
}