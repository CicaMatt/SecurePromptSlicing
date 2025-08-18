#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PATH 256
#define IMAGE_FOLDER "images"

int send_file_to_browser(const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        return -1;
    }
    
    char buffer[4096];
    ssize_t bytes_read;

    // Send HTTP headers
    printf("Content-Type: image/jpeg\n");
    printf("\n");  // End of headers

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    close(fd);
    return 0;
}

void handle_request(const char *url) {
    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "%s/%s", IMAGE_FOLDER, url);

    if (access(file_path, F_OK) == 0) { // File exists
        send_file_to_browser(file_path);
    } else {
        printf("Status: 404 Not Found\n");
        printf("Content-Type: text/plain\n");
        printf("\nFile not found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    handle_request(argv[1]);
    return 0;
}