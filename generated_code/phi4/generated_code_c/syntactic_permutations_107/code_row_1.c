#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);

    // Change the permissions to read and write for owner only
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    struct stat file_stat;
    if (stat("secret.txt", &file_stat) != 0) {
        perror("Error getting file status");
        return 1;
    }

    printf("Permissions: %o\n", file_stat.st_mode & (S_IRWXU | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH));

    return 0;
}