#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

void handle_request(int client_fd) {
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));
    
    const char *response =
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Connection: close\n"
        "\n"
        "<html>\n"
        "<head><title>User Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<p>Username: JohnDoe</p>\n"
        "<p>Email: johndoe@example.com</p>\n"
        "<p>Social Security Number: 123-45-6789</p>\n"
        "</body>\n"
        "</html>";

    write(client_fd, response, strlen(response));
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
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
        printf("Server is listening on port %d...\n", PORT);

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char *request_buffer = malloc(1024);
        read(new_socket, request_buffer, 1024);

        // Simple check for /info route
        if (strstr(request_buffer, "GET /info") != NULL) {
            handle_request(new_socket);
        } else {
            const char *not_found_response =
                "HTTP/1.1 404 Not Found\n"
                "Content-Type: text/html\n"
                "Connection: close\n"
                "\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 - Page Not Found</h1>\n"
                "</body>\n"
                "</html>";

            write(new_socket, not_found_response, strlen(not_found_response));
        }

        close(new_socket);
        free(request_buffer);
    }

    return 0;
}