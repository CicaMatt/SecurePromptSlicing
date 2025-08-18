#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *filename = "secret.txt";
    const char *info = "This is super secret info.";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", info);
    fclose(file);
    
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}