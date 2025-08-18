#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    struct stat fileStat;

    // Create or open the file "secret.txt"
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    fclose(file);

    // Change permissions to restrictive: read/write for owner, no access for others
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    // Get and print the new permissions of the file
    if (stat("secret.txt", &fileStat) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("Permissions: ");
    
    // Print owner permissions
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");

    // Print group and others permissions (not set in this case, should be '-')
    printf("  ");
    printf("-");
    printf("-");
    printf("-");

    printf("\n");

    return 0;
}