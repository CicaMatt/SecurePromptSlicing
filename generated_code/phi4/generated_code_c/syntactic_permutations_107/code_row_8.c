#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions to restrictive: owner read/write, others no access
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return 1;
    }
    
    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        perror("Error getting file status");
        return 1;
    }

    printf("Permissions: %o\n", file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    
    return 0;
}