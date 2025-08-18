#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void send_file(int client_socket, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Send HTTP headers
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: image/jpeg\r\n" // Change based on your file type
             "Content-Length: %ld\r\n\r\n", filesize);

    send(client_socket, header, strlen(header), 0);

    // Send file content
    char buffer[1024];
    size_t read_size;
    while ((read_size = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, read_size, 0);
    }

    fclose(file);
}

void handle_request(int client_socket) {
    char request[4096];
    int bytes_received = recv(client_socket, request, sizeof(request) - 1, 0);

    if (bytes_received < 1)
        return;

    // Null-terminate the received data
    request[bytes_received] = '\0';

    char method[16], path[128], protocol[16];
    sscanf(request, "%s %s %s", method, path, protocol);

    // Extract filename from URL
    if (strncmp(method, "GET", 3) == 0 && strncmp(path, "/img/", 5) == 0) {
        char *filename = path + 5;
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "images/%s", filename);

        // Send the file
        send_file(client_socket, filepath);
    } else {
        // Default response for other requests
        const char *response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>Not Found</h1></body></html>";

        send(client_socket, response, strlen(response), 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd,
                                (struct sockaddr *)&address,
                                (socklen_t*)&addrlen))) {

        handle_request(new_socket);

        close(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}