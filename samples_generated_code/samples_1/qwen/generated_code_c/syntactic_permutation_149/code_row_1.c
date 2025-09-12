#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void insert_user_message_in_db(const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message into database: %s\n", message);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "GET /post")) {
        const char *message_start = strstr(buffer, "message=");
        if (message_start != NULL) {
            message_start += 8;
            char message[BUFFER_SIZE] = {0};
            sscanf(message_start, "%[^ \r\n]", message);
            insert_user_message_in_db(message);

            const char *redirect_response = "HTTP/1.1 302 Found\r\nLocation: /\r\nConnection: close\r\n\r\n";
            send(client_socket, redirect_response, strlen(redirect_response), 0);
        }
    } else if (strstr(buffer, "GET /")) {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                               "<html><body>"
                               "<h1>Messages</h1>"
                               "<form action=\"/post\" method=\"get\">"
                               "<input type=\"text\" name=\"message\"><br>"
                               "<input type=\"submit\" value=\"Submit\">"
                               "</form>"
                               "<p>Message 1</p>"
                               "<p>Message 2</p>"
                               "</body></html>";
        send(client_socket, response, strlen(response), 0);
    }
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

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}