#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Set restrictive permissions: Owner can read and write, others cannot access
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}