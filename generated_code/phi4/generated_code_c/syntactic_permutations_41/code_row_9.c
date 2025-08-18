#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

void handle_request(const char *request_path, const char *username, const char *email, const char *ssn) {
    if (strcmp(request_path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>User Information</h1>");
        printf("<p>Username: %s</p>", username);
        printf("<p>Email: %s</p>", email);
        printf("<p>Last 4 Digits of SSN: %.4s</p>", &ssn[strlen(ssn) - 4]);
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char buffer[1024];
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(client_socket, buffer, sizeof(buffer));

        // Simulating user data retrieval
        const char *username = "JohnDoe";
        const char *email = "john.doe@example.com";
        const char *ssn = "123-45-6789";

        handle_request(buffer, username, email, ssn);

        close(client_socket);
    }

    close(server_socket);
    return 0;
}