#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "<html>\n"
        "<head><title>Info</title></head>\n"
        "<body>\n"
        "<h1>User Information</h1>\n"
        "<p>Username: JohnDoe</p>\n"
        "<p>Email: john.doe@example.com</p>\n"
        "<p>Last 4 of SSN: 1234</p>\n"
        "</body>\n"
        "</html>\n";

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);

        // Check for the /info route
        if (strstr(buffer, "GET /info") != NULL) {
            handle_request(client_socket);
        } else {
            const char *response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 Not Found</h1>\n"
                "</body>\n"
                "</html>\n";

            send(client_socket, response, strlen(response), 0);
        }

        close(client_socket);
    }

    // Close the server socket
    close(server_fd);

    return 0;
}