#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(char *request) {
    char method[10], path[256], filename[256];
    sscanf(request, "%s %s", method, path);

    if (strcmp(method, "POST") == 0 && strncmp(path, "/upload", 7) == 0) {
        char *content_disposition = strstr(request, "Content-Disposition");
        char *filename_start = strstr(content_disposition, "filename=\"") + 10;
        char *filename_end = strchr(filename_start, '"');
        strncpy(filename, filename_start, filename_end - filename_start);
        filename[filename_end - filename_start] = '\0';

        char *data_start = strstr(request, "\r\n\r\n") + 4;

        int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd != -1) {
            write(fd, data_start, strlen(data_start));
            close(fd);
            printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.\n");
        } else {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\nFailed to save file.\n");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\nNot found.\n");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    while (1) {
        ssize_t bytes_read = read(0, request, MAX_REQUEST_SIZE - 1);
        if (bytes_read > 0) {
            request[bytes_read] = '\0';
            handle_request(request);
            break;
        }
    }
    return 0;
}