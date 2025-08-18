#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file to be restrictive (read/write/execute for owner only)
    if (chmod("secret.txt", S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Print the content of the file
    file = fopen("secret.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}