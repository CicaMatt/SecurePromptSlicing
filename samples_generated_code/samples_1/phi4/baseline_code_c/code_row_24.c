#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} UserInfo;

UserInfo getUserInfo() {
    return (UserInfo) { .username = "user123", .email = "user@example.com", .ssn_last_4 = "6789" };
}

void sendResponse(int client_socket, const char *response) {
    send(client_socket, response, strlen(response), 0);
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0 && strstr(buffer, "GET /info")) {
            UserInfo info = getUserInfo();
            
            char response[1024];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html\r\n"
                     "\r\n"
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 digits of SSN: %s</p>"
                     "</body></html>",
                     info.username, info.email, info.ssn_last_4);

            sendResponse(new_socket, response);
        } else {
            char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
            sendResponse(new_socket, response);
        }

        close(new_socket);
    }

    return 0;
}