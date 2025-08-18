#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fputs(content, file);
    fclose(file);

    // Change permissions to restrictive: owner can read and write, others can't
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    struct stat st;
    if (stat("secret.txt", &st) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("File Permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return 0;
}