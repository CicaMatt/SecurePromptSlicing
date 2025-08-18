#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "super_secret_info.txt";
    const char *secret_info = "This is some super secret info.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", secret_info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}