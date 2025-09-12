#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

void extract_tar(const char* tar_path, const char* dest_dir) {
    char command[1024];
    
    snprintf(command, sizeof(command), "tar -xzf %s -C %s", tar_path, dest_dir);
    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "Failed to extract the tar file: %s\n", tar_path);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* tar_file = argv[1];
    const char* destination_dir = argv[2];

#ifdef _WIN32
    if (_mkdir(destination_dir) != 0 && errno != EEXIST) {
        fprintf(stderr, "Failed to create directory: %s\n", destination_dir);
        return EXIT_FAILURE;
    }
#else
    if (mkdir(destination_dir, 0777) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        return EXIT_FAILURE;
    }
#endif

    extract_tar(tar_file, destination_dir);

    FILE* file = fopen("/tmp/unpack/info.txt", "w+");
    if (!file) {
        fprintf(stderr, "Failed to open file: /tmp/unpack/info.txt\n");
        return EXIT_FAILURE;
    }

    const char* text = "This is a sample info file.";
    fwrite(text, sizeof(char), strlen(text), file);
    
    fclose(file);

    return 0;
}