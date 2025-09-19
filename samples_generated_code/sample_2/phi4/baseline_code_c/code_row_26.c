#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Open or create the file "important_config" with read and write permissions for owner, and no permissions for others.
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(file);

    // Change the permissions of the file to read and write for owner only
    if (chmod("important_config", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    printf("File 'important_config' created with necessary permissions.\n");

    return 0;
}