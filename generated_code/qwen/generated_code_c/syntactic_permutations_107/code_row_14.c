#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);
    
    if (chmod("secret.txt", 0000) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    struct stat fileStat;
    if(stat("secret.txt",&fileStat) < 0) {        
        perror("Failed to get file stats");
        return EXIT_FAILURE;
    }
    
    printf("Permissions: %d\n", (int)fileStat.st_mode & 0777);

    return EXIT_SUCCESS;
}