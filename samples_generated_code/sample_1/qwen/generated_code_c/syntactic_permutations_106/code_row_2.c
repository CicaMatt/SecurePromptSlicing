#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "supersecretinfo.txt";
    const char *secret_info = "This is some super secret information.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s\n", secret_info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", filename);
    
    return 0;
}