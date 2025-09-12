#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[256];
            sscanf(buffer, "filename=\"%[^\"]", filename);
            fp = fopen(filename, "wb");
            if (!fp) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 34\r\n\r\nFailed to open file for writing.", 89, 0);
                break;
            }
            char *file_content = strstr(buffer, "\r\n\r\n") + 4;
            fwrite(file_content, 1, bytes_received - (file_content - buffer), fp);
            fclose(fp);
            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 35\r\n\r\nFile uploaded successfully.", 68, 0);
        } else {
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 194\r\n"
                "\r\n"
                "<html><body>"
                "<form method='post' action='/upload' enctype='multipart/form-data'>"
                "Upload a file: <input type='file' name='file'><br>"
                "<input type='submit'>"
                "</form></body></html>";
            send(client_socket, response, strlen(response), 0);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}