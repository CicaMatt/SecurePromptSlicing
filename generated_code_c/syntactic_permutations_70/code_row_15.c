/*
 *  Simple http server for uploading files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PORT 8081
#define MAX_FILE_SIZE (5 * 1024 * 1024) /* 5MB */
#define MAX_REQUEST_BODY_SIZE (10 * 1024 * 1024) /* 10 MB */

void upload_file(char *file_name, char *content_type, void *data, size_t data_size) {
    FILE *f;
    f = fopen(file_name, "wb");
    if (f == NULL) {
        printf("error creating file: %s\n", strerror(errno));
        return;
    }
    size_t bytes_written = fwrite(data, 1, data_size, f);
    if (bytes_written != data_size) {
        printf("error writing to file: %s\n", strerror(errno));
        fclose(f);
        return;
    }
    fclose(f);
}

int main() {
    char *html = "<html><body><h1>File upload</h1><form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"my_file\"><br/><input type=\"submit\" value=\"Upload\"></form></body></html>";
    char *port = "8081";
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t client_size;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        printf("error creating socket: %s\n", strerror(errno));
        return -1;
    }

    int enable = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        printf("error setting socket options: %s\n", strerror(errno));
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("error binding socket: %s\n", strerror(errno));
        return -1;
    }

    listen(server_fd, 5);

    while (1) {
        client_size = sizeof(client);
        client_fd = accept(server_fd, (struct sockaddr *)&client, &client_size);
        if (client_fd < 0) {
            printf("error accepting connection: %s\n", strerror(errno));
            continue;
        }

        char request[MAX_REQUEST_BODY_SIZE];
        ssize_t bytes = recv(client_fd, &request, sizeof(request), 0);
        if (bytes < 0) {
            printf("error reading from socket: %s\n", strerror(errno));
            close(client_fd);
            continue;
        }
        request[bytes] = '\0';

        char file_name[64];
        sprintf(file_name, "/uploads/%d", time(NULL));

        upload_file(file_name, "image/jpeg", request, bytes);

        char response[] = "<html><body>File uploaded successfully</body></html>";
        send(client_fd, response, strlen(response), 0);

        close(client_fd);
    }
}