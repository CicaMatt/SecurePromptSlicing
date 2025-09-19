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

int main() {
    char current_dir[FILENAME_MAX];
    if (!GetCurrentDir(current_dir, sizeof(current_dir))) {
        printf("Error getting the current directory.\n");
        return 1;
    }

    FILE *zip = fopen("archive.zip", "rb");
    if (zip == NULL) {
        perror("Failed to open archive.zip");
        return 1;
    }
    
    // For demonstration, we just print that extraction is happening
    printf("Extracting all files from archive.zip...\n");

    // Normally, here you would use a library like libarchive or minizip to extract the zip contents.
    // This example does not perform actual extraction as it requires third-party libraries.

    fclose(zip);

    return 0;
}
