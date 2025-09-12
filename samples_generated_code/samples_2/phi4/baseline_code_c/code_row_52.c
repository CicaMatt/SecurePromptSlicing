#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    struct stat fileInfo;
    if (stat("secret.txt", &fileInfo) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Set permissions to owner: read/write, group and others: no permission
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file mode");
        return EXIT_FAILURE;
    }

    // Get the updated file status
    if (stat("secret.txt", &fileInfo) != 0) {
        perror("Error getting file status after chmod");
        return EXIT_FAILURE;
    }
    
    printf("Permissions of 'secret.txt': %lo\n", fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    
    return EXIT_SUCCESS;
}