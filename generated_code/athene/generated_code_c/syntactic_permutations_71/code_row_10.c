#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define FILE_UPLOAD_PATH "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, file_size;
    FILE *fp;

    // Read HTTP request line and headers
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "Content-Length:")) {
            sscanf(buffer, "Content-Length: %d", &file_size);
        }
        if (strstr(buffer, "\r\n\r\n")) break;
    }

    // Create upload directory if it does not exist
    mkdir(FILE_UPLOAD_PATH, 0755);

    // Open file for writing
    char filename[256];
    sscanf(buffer, "filename=\"%[^\"]", filename);
    snprintf(filename, sizeof(filename), "%s%s", FILE_UPLOAD_PATH, basename(filename));
    fp = fopen(filename, "wb");

    if (fp == NULL) {
        perror("Failed to open file");
        close(client_socket);
        return;
    }

    // Receive and write file data
    while (file_size > 0) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        fwrite(buffer, 1, bytes_received, fp);
        file_size -= bytes_received;
    }

    fclose(fp);

    // Send HTTP response
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body>File uploaded successfully</body></html>";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept new connection
        client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}