#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fwrite(secret_info, sizeof(char), strlen(secret_info), file);
    fclose(file);

    // Change the file mode to read-only for the owner
    struct stat sb;
    if (stat(filename, &sb) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    if (chmod(filename, sb.st_mode & ~S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}