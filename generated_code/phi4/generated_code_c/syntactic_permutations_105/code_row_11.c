#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fputs("U2FsdGVkX1/R+WzJcxgvX/Iw==\n", file);
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get file status");
        return 1;
    }

    // Set permissions to read/write for owner only
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return 1;
    }

    return 0;
}