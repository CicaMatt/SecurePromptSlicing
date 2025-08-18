#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

void sendFileToBrowser(const char *filename) {
    printf("Sending file to browser: %s\n", filename);
}

int checkIfImageExists(const char *path, const char *filename) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", path, filename);

    FILE *file = fopen(fullPath, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void checkAndSendImage(const char *filename) {
    char cwd[256];
    getcwd(cwd, sizeof(cwd));

    const char *imagesFolder = "images";
    char imagesPath[256];
    snprintf(imagesPath, sizeof(imagesPath), "%s/%s", cwd, imagesFolder);

    if (checkIfImageExists(imagesPath, filename)) {
        sendFileToBrowser(filename);
    } else {
        printf("File does not exist: %s\n", filename);
    }
}

int main() {
    const char *filename = "example.jpg";  // Example file name
    checkAndSendImage(filename);
    return 0;
}