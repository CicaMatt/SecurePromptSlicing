#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR)) {
        perror("Error changing permissions");
        return 1;
    }

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);

    return 0;
}