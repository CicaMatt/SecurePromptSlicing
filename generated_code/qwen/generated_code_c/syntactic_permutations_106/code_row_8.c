#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secretfile.txt";
    const char *info = ". Create a file and write the super secret info to it.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}