#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "./images/"

int check_file_exists(const char *filename) {
    struct stat buffer;
    if (stat(IMAGES_FOLDER filename, &buffer) == 0) {
        return 1; // File exists
    }
    return 0; // File does not exist
}

void send_file_to_browser(const char *url) {
    printf("Sending file to browser: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    if (check_file_exists(filename)) {
        send_file_to_browser(IMAGES_FOLDER filename);
    } else {
        printf("File does not exist\n");
    }
    
    return 0;
}
