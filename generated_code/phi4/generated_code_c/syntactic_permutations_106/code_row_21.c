#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    FILE *file;
    file = fopen("secret.txt", "w");
    
    if (file == NULL) {
        perror("Failed to create the file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", secretInfo);
    fclose(file);

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    // Change the permissions of the file to owner read/write/execute
    if (chmod("secret.txt", S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }
    
    printf("File name: secret.txt\n");

    return EXIT_SUCCESS;
}