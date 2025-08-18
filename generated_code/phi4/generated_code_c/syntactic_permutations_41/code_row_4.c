#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

void handle_client(int client_sock) {
    char response[] = 
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n\n"
        "<html><body>\n"
        "<h1>User Information</h1>\n"
        "<p>Username: user123</p>\n"
        "<p>Email: user@example.com</p>\n"
        "<p>Last 4 digits of SSN: 1234</p>\n"
        "</body></html>";

    send(client_sock, response, strlen(response), 0);
    close(client_sock);
}

int main() {
    int server_fd, client_sock;
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        read(client_sock, buffer, sizeof(buffer));

        // Check if the request is for /info
        if (strstr(buffer, "GET /info") != NULL) {
            handle_client(client_sock);
        } else {
            char not_found_response[] =
                "HTTP/1.1 404 Not Found\n"
                "Content-Type: text/html\n\n"
                "<html><body>\n"
                "<h1>404 Not Found</h1>\n"
                "</body></html>";
            send(client_sock, not_found_response, strlen(not_found_response), 0);
        }

        close(client_sock);
    }

    return 0;
}