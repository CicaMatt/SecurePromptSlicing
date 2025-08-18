#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "./images/"
#define MAX_PATH_LENGTH 256

int check_file_exists(const char *filename) {
    struct stat buffer;
    return (stat(IMAGES_FOLDER filename, &buffer) == 0);
}

void send_file(const char *filename) {
    FILE *file = fopen(IMAGES_FOLDER filename, "rb");
    if (!file) {
        printf("File not found.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(filesize + 1);
    fread(data, 1, filesize, file);
    data[filesize] = '\0';
    fclose(file);

    printf("Sending file: %s\n", filename);
    // Simulate sending the file by printing its contents
    printf("%s\n", data);
    free(data);
}

void handle_request(const char *url) {
    const char *filename = strrchr(url, '/') + 1;
    if (filename && check_file_exists(filename)) {
        send_file(filename);
    } else {
        printf("File not found.\n");
    }
}

int main() {
    const char *url = "/images/example.jpg";
    handle_request(url);
    return 0;
}