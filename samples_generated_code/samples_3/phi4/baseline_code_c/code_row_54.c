#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define EXTRACT_CMD "tar -xf"
#else
    #define EXTRACT_CMD "tar xf"
#endif

void extract_tar(const char *archive, const char *destination) {
    char command[256];
    snprintf(command, sizeof(command), "%s %s -C %s", EXTRACT_CMD, archive, destination);
    
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to extract %s\n", archive);
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *archive = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    // Extract the tar file
    extract_tar(archive, destination);

    printf("Extraction completed.\n");

    // Open a file from the extracted contents for demonstration
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/example.txt", destination);
    FILE *file = fopen(filepath, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Failed to open %s\n", filepath);
        return EXIT_FAILURE;
    }

    printf("Contents of example.txt:\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    fclose(file);

    return 0;
}