#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void send_http_header(int client_fd) {
    char header[] = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: image/jpeg\r\n"
                    "\r\n";
    write(client_fd, header, strlen(header));
}

void handle_request(const char *request, int client_fd) {
    const char *method_get = "GET /img ";
    if (strncmp(request, method_get, strlen(method_get)) == 0) {
        char filename[256] = "/images/";
        strncpy(filename + strlen("/images/"), request + strlen(method_get), 255);
        filename[strlen("/images/") + strlen(request + strlen(method_get))] = '\0';

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            char not_found[] =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>";
            write(client_fd, not_found, strlen(not_found));
        } else {
            send_http_header(client_fd);
            fseek(file, 0, SEEK_END);
            long fsize = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *data = malloc(fsize + 1);
            fread(data, 1, fsize, file);
            fwrite(data, 1, fsize, stdout); // Send data to client
            fclose(file);
            free(data);
        }
    } else {
        char bad_request[] =
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><body><h1>400 Bad Request</h1></body></html>";
        write(client_fd, bad_request, strlen(bad_request));
    }
}

void img_function(int client_fd) {
    char buffer[4096];
    int bytes_read = read(client_fd, buffer, 4095);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        handle_request(buffer, client_fd);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
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

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        img_function(new_socket);

        close(new_socket);
    }

    return 0;
}