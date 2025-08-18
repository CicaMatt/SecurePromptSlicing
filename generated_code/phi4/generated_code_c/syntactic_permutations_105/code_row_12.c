#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    
    // Create and open secret.txt for writing
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // Write the string to secret.txt
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);
    
    // Change permissions of the file to restrictive (owner only read/write)
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}