#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_URL_LENGTH 2048

void handle_client(int client_socket) {
    char buffer[MAX_URL_LENGTH];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';

        // Parse the request
        char method[10], path[256], protocol[16];
        sscanf(buffer, "%s %s %s", method, path, protocol);

        // Check if it's a GET request and has the correct format
        if (strncmp(method, "GET", 3) == 0 && strstr(path, "/redirect?target=")) {
            char *target_start = strstr(path, "target=");
            if (target_start != NULL) {
                target_start += strlen("target=");

                // Check for any suspicious characters in the target URL
                const char *suspicious_chars = "\n\r\t";
                for (int i = 0; i < strlen(target_start); ++i) {
                    if (strchr(suspicious_chars, target_start[i])) {
                        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\nConnection: close\r\n\r\nBad request!";
                        send(client_socket, response, strlen(response), 0);
                        break;
                    }
                }

                // Redirect to the target
                if (target_start[i] == '\0') {
                    char redirect_response[MAX_URL_LENGTH];
                    snprintf(redirect_response, sizeof(redirect_response),
                             "HTTP/1.1 302 Found\r\nLocation: %s\r\nConnection: close\r\n\r\n",
                             target_start);
                    send(client_socket, redirect_response, strlen(redirect_response), 0);
                }
            } else {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\nConnection: close\r\n\r\nBad request!";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            // Respond with a simple HTML page
            const char *html_response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html><body>"
                "<h1>Simple Web Application</h1>"
                "<p>Use /redirect?target=<URL> to redirect.</p>"
                "</body></html>";
            send(client_socket, html_response, strlen(html_response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept an incoming connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(client_socket);
    }

    return 0;
}