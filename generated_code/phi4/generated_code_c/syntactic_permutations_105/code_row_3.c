#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *text = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(text, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change permissions of the file to read/write by owner only
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}