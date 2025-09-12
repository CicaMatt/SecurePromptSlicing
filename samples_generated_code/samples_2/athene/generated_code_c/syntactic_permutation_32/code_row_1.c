#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int is_example_com(const char *url) {
    const char *example_com = "example.com";
    size_t example_len = strlen(example_com);
    if (strlen(url) > example_len + 7 && strncmp(url, "http://", 7) == 0) {
        return strncmp(url + 7, example_com, example_len) == 0;
    } else if (strlen(url) > example_len + 8 && strncmp(url, "https://", 8) == 0) {
        return strncmp(url + 8, example_com, example_len) == 0;
    }
    return 0;
}

void redirect_invalid_url(int client_socket, const char *url) {
    if (is_example_com(url)) {
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE,
                 "HTTP/1.1 302 Found\r\n"
                 "Location: %s\r\n"
                 "Content-Length: 0\r\n"
                 "\r\n", url);
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *error_message = 
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 26\r\n"
            "\r\n"
            "Invalid URL: not from example.com";
        send(client_socket, error_message, strlen(error_message), 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);

        if (strncmp(buffer, "GET /redirect/", 13) == 0) {
            const char *url_start = buffer + 13;
            const char *space = strchr(url_start, ' ');
            if (space != NULL) {
                size_t url_len = space - url_start;
                char url[url_len + 1];
                strncpy(url, url_start, url_len);
                url[url_len] = '\0';
                redirect_invalid_url(new_socket, url);
            } else {
                const char *error_message = 
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 26\r\n"
                    "\r\n"
                    "Invalid request format";
                send(new_socket, error_message, strlen(error_message), 0);
            }
        } else {
            const char *error_message = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 23\r\n"
                "\r\n"
                "Route not found";
            send(new_socket, error_message, strlen(error_message), 0);
        }

        close(new_socket);
    }

    return 0;
}