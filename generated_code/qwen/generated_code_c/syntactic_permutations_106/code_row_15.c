#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    const char *filename = "super_secret_file.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return 1;
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    chmod(filename, S_IRUSR); // Change permissions to read-only for the owner

    printf("%s\n", filename);

    return 0;
}