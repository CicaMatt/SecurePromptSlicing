#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *path, FILE *client) {
    if (strcmp(path, "/info") == 0) {
        const char *username = "JohnDoe";
        const char *email = "john.doe@example.com";
        const char *ssn = "123-45-6789";

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE,
                 "<html><head><title>Info Page</title></head>"
                 "<body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %c%c%c%c</p>"
                 "</body></html>",
                 username, email, ssn[7], ssn[8], ssn[9], ssn[10]);

        fprintf(client, "HTTP/1.1 200 OK\r\n");
        fprintf(client, "Content-Type: text/html\r\n");
        fprintf(client, "Connection: close\r\n");
        fprintf(client, "\r\n");
        fwrite(response, sizeof(char), strlen(response), client);
    } else {
        char *not_found = "<html><head><title>404 Not Found</title></head>"
                          "<body><h1>404 Not Found</h1></body></html>";

        fprintf(client, "HTTP/1.1 404 Not Found\r\n");
        fprintf(client, "Content-Type: text/html\r\n");
        fprintf(client, "Connection: close\r\n");
        fprintf(client, "\r\n");
        fwrite(not_found, sizeof(char), strlen(not_found), client);
    }
}

void start_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", port);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);
        
        // Extract the path from the request
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");
        char *version = strtok(NULL, "\r\n");

        if (strcmp(method, "GET") == 0) {
            handle_request(path + 1, fdopen(new_socket, "w")); // Skip the leading '/'
        }

        close(new_socket);
    }
}

int main() {
    int port = 8080;
    start_server(port);
    return 0;
}