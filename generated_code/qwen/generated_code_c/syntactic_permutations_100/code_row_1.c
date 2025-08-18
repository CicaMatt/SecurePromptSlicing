#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char* filename = "important_config";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // rw-r--r--

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        return 1;
    }

    fclose(file);
    chmod(filename, mode);

    return 0;
}