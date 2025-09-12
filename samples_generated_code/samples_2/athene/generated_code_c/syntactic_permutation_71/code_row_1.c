#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, file_size;
    FILE *fp;

    // Read HTTP request
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            // Parse Content-Length header to get file size
            char *content_length_header = strstr(buffer, "Content-Length:");
            if (content_length_header != NULL) {
                sscanf(content_length_header + 15, "%d", &file_size);

                // Skip headers
                while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, MSG_PEEK)) > 0 && buffer[0] != '\r' && buffer[1] != '\n') {
                    recv(client_socket, buffer, bytes_received, 0);
                }
                recv(client_socket, buffer, 4, 0); // Consume CRLF

                // Save file
                fp = fopen("uploaded_file", "wb");
                while (file_size > 0) {
                    int chunk_size = file_size < BUFFER_SIZE ? file_size : BUFFER_SIZE;
                    bytes_received = recv(client_socket, buffer, chunk_size, 0);
                    fwrite(buffer, 1, bytes_received, fp);
                    file_size -= bytes_received;
                }
                fclose(fp);

                // Send response
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            // Send simple HTML form for file upload
            const char *response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n\r\n"
                "<html><body>"
                "<h1>Upload File</h1>"
                "<form method='post' action='/upload' enctype='multipart/form-data'>"
                "<input type='file' name='file'><br><br>"
                "<input type='submit' value='Upload'>"
                "</form></body></html>";
            send(client_socket, response, strlen(response), 0);
        }
        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}