#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));
    
    const char *username = "JohnDoe";
    const char *email = "johndoe@example.com";
    const char *ssn_last_4 = "1234";

    char response[512];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: ****%s</p>"
             "</body></html>",
             username, email, ssn_last_4);

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
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

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        char request[1024] = {0};
        read(new_socket, request, sizeof(request));
        
        // Simple request parsing for demonstration purposes
        if (strstr(request, "GET /info")) {
            handle_request(new_socket);
        } else {
            const char *not_found_response = 
                "<html><body><h1>404 Not Found</h1></body></html>";
            write(new_socket, not_found_response, strlen(not_found_response));
            close(new_socket);
        }
    }

    return 0;
}