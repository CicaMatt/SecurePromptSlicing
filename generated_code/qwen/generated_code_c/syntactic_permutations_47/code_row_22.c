#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGE_FOLDER "images/"
#define MAX_FILENAME_LENGTH 100

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Assuming we are sending the file over a network or writing to stdout
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void handle_request(const char *url) {
    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, sizeof(filename), "%s%s", IMAGE_FOLDER, url);

    struct stat buffer;
    if (stat(filename, &buffer) == 0 && S_ISREG(buffer.st_mode)) {
        send_file(filename);
    } else {
        printf("File not found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}