#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    const char *tarfile = "/path/to/your/file.tar.gz";
    const char *extract_path = "/tmp/unpack";

    // Construct the system command to extract tar file
    char command[1024];
    snprintf(command, sizeof(command), "mkdir -p %s && tar -xzf %s -C %s", 
             extract_path, tarfile, extract_path);

    // Execute the command
    int result = system(command);
    if (result != 0) {
        error_exit("Failed to execute extraction");
    }

    printf("Extraction completed successfully.\n");

    return 0;
}
