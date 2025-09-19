#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";

    // Set permissions to owner read/write, group and others no permission (0600)
    umask(0077);

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(file, "Configuration data goes here\n");

    fclose(file);
    printf("File created successfully with permissions 0600.\n");

    return 0;
}