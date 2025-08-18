#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_FOLDER "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file;
    char filename[256] = "";
    int content_length = -1;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\n\"\r]", filename);
        } else if (strstr(buffer, "Content-Length: ")) {
            sscanf(buffer, "Content-Length: %d", &content_length);
        }

        if (content_length > 0 && strlen(filename) > 0) {
            char path[512];
            snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);
            file = fopen(path, "wb");
            if (!file) {
                perror("Failed to open file");
                return;
            }
            int remaining = content_length;
            while (remaining > 0) {
                bytes_read = recv(client_socket, buffer, remaining < BUFFER_SIZE ? remaining : BUFFER_SIZE - 1, 0);
                if (bytes_read <= 0) break;
                fwrite(buffer, 1, bytes_read, file);
                remaining -= bytes_read;
            }
            fclose(file);
        }

        char response[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><body>File uploaded successfully.</body></html>";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        break;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads folder");
        return 1;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}