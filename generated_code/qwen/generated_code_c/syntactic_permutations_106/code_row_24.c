#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s\n", secret_info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("Super secret info written to %s and permissions set to read-only for the owner.\n", filename);
    
    return 0;
}