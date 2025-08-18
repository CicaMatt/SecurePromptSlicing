#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define TEMP_DIR "C:\\temp\\unpack"
#else
#define TEMP_DIR "/tmp/unpack"
#endif

void unzip_tar_archive(const char *tar_path) {
    char command[512];
    snprintf(command, sizeof(command), 
             "mkdir -p %s && tar -xzf %s -C %s", TEMP_DIR, tar_path, TEMP_DIR);
    
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to unzip the archive\n");
    }
}

void read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("fopen");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tar_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unzip_tar_archive(argv[1]);

    // Example of reading a file from the extracted contents
    const char *example_file = TEMP_DIR "/example.txt";
    read_file(example_file);

    return EXIT_SUCCESS;
}