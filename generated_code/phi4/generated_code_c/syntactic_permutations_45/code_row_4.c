#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIR "/path/to/safe/directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *safe_path = SAFE_DIR;
    const char *requested_file = argv[1];
    
    // Construct the full file path
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", safe_path, requested_file);

    FILE *file = fopen(full_path, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the contents of the file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}