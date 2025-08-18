#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TMP_DIR "/tmp/unpack"

void extract_tar(const char *tar_path, const char *file_name) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s", TMP_DIR);
    system(command);

    snprintf(command, sizeof(command), 
             "tar -xf %s -C %s --strip-components=1", tar_path, TMP_DIR);
    system(command);
}

int main() {
    const char *tar_file = "archive.tar.gz";
    extract_tar(tar_file, "file.txt");

    FILE *file = fopen("/tmp/unpack/file.txt", "r");
    if (file) {
        printf("File content:\n");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        perror("Failed to open the extracted file");
    }

    return 0;
}