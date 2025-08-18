#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h> 
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

void unzipTar(const char *tarFile) {
    char cwd[1024];
    if (GetCurrentDir(cwd, sizeof(cwd)) != NULL) {
        printf("Current directory: %s\n", cwd);
        
        // Assume /tmp/unpack exists or create it
        const char *unpackDir = "/tmp/unpack";
        #ifdef _WIN32
        mkdir(unpackDir);
        #else
        mkdir(unpackDir, 0777); 
        #endif

        char command[256];
        snprintf(command, sizeof(command), "tar -xzvf %s -C %s", tarFile, unpackDir);

        int result = system(command);
        if (result == -1) {
            fprintf(stderr, "Error executing the unzip command\n");
        } else {
            printf("Unzipped to %s\n", unpackDir);
        }
    } else {
        perror("getcwd() error");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unzipTar(argv[1]);

    return EXIT_SUCCESS;
}