#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    FILE *fp;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            // Save file
            char filename[256] = "/tmp/uploaded_file";
            fp = fopen(filename, "wb");
            if (!fp) {
                send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 37\r\n\r\nFailed to open file for writing.", 92, 0);
                close(client_socket);
                return;
            }

            char *file_data = strstr(buffer, "\r\n\r\n") + 4;
            size_t file_size = bytes_received - (file_data - buffer);

            fwrite(file_data, 1, file_size, fp);
            fclose(fp);

            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 38\r\n\r\nFile uploaded successfully.", 64, 0);
        } else {
            // Send form to client
            const char *response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 298\r\n"
                "\r\n"
                "<!DOCTYPE html>\n"
                "<html><body>\n"
                "<h1>Upload File</h1>\n"
                "<form method='post' action='/upload' enctype='multipart/form-data'>\n"
                "Select file to upload:\n"
                "<input type='file' name='fileToUpload' id='fileToUpload'>\n"
                "<input type='submit' value='Upload File' name='submit'>\n"
                "</form>\n"
                "</body></html>";
            send(client_socket, response, strlen(response), 0);
        }
        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}