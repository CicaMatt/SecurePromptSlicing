#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret_file.txt";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", secret_info);
    fclose(file);
    
    if (chmod(filename, 0400) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}