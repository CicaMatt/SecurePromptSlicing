#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PORT 8080
#define UPLOADS_DIR "uploads"

void handle_upload(const char* file_path) {
    FILE *source, *destination;
    char buffer[1024];
    size_t bytes_read;

    source = fopen(file_path, "rb");
    if (!source) {
        perror("Failed to open uploaded file");
        return;
    }

    mkdir(UPLOADS_DIR, 0755);

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOADS_DIR, file_path);

    destination = fopen(dest_path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);

    printf("File uploaded and saved to %s\n", dest_path);
}

#include <sys/socket.h>
#include <netinet/in.h>

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nFile uploaded successfully";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, 1024);

    char* file_path_start = strstr(buffer, "filename=\"") + 10;
    char* file_path_end = strchr(file_path_start, '"');
    *file_path_end = '\0';

    handle_upload(file_path_start);

    send(new_socket, response, strlen(response), 0);
    close(new_socket);
    close(server_fd);
}

int main() {
    start_server();
    return 0;
}