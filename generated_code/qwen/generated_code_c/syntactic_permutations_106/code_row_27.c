#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
    const char *secret_info = "This is some super secret info!";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s", secret_info);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);
    
    return 0;
}