#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fprintf(file, "%s\n", data) < 0) {
        fclose(file);
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change the permissions of secret.txt to be restrictive
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Print the permissions of secret.txt
    printf("Permissions for 'secret.txt': %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}