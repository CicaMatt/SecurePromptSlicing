#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is super secret information.";
    const char *filename = "super_secret.txt";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s", secret_info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", filename);
    
    return 0;
}