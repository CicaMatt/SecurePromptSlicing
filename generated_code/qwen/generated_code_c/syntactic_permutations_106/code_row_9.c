#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "supersecret.txt";
    const char *info = "This is some super secret info.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s", info);
    fclose(file);
    
    if (chmod(filename, 0400) < 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", filename);
    
    return 0;
}