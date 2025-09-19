#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *filename = "supersecret.txt";
    const char *info = "This is some super secret information.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", info);
    fclose(file);
    
    if (chmod(filename, 0400) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}