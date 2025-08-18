#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"

void createUploadsDir() {
    struct stat st = {0};

    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }
}

int main() {
    // Create the uploads directory if it doesn't exist
    createUploadsDir();

    printf("Web app setup completed. Files will be saved in the '%s' folder.\n", UPLOADS_DIR);

    return 0;
}