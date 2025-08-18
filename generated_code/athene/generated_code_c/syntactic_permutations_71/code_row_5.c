#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_FILENAME_LENGTH 256

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    char filename[MAX_FILENAME_LENGTH] = "uploads/";
    ssize_t num_bytes;

    // Read request and parse for file upload boundary
    while ((num_bytes = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        if (strstr(buffer, "Content-Disposition: form-data; name=\"file\"; filename=")) {
            sscanf(buffer, "Content-Disposition: form-data; name=\"file\"; filename=\"%[^\n]", filename + strlen("uploads/"));
            FILE *fp = fopen(filename, "wb");
            if (!fp) {
                perror("Failed to open file");
                close(client_socket);
                return;
            }
            while ((num_bytes = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
                if (strstr(buffer, "--")) break; // End of file
                fwrite(buffer, 1, num_bytes, fp);
            }
            fclose(fp);
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
            send(client_socket, response, strlen(response), 0);
            break;
        } else {
            // Send a simple HTML form if no file is being uploaded
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                                   "<html><body>"
                                   "<form action=\"/\" method=\"post\" enctype=\"multipart/form-data\">"
                                   "<input type=\"file\" name=\"file\" />"
                                   "<input type=\"submit\" value=\"Upload\" />"
                                   "</form></body></html>";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}