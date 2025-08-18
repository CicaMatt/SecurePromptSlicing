#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        fclose(file);
        perror("Error writing to file");
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change permissions
    struct stat st;
    if (stat("secret.txt", &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    mode_t new_permissions = st.st_mode & ~S_IRWXU | S_IREAD;  // Make it read-only for user
    if (chmod("secret.txt", new_permissions) == -1) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    // Print the permissions
    printf("Permissions of secret.txt: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return 0;
}