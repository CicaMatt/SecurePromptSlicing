#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
    int fd;
} connection;

void handle_request(connection *conn) {
    char buffer[BUFFER_SIZE];
    recv(conn->fd, buffer, sizeof(buffer), 0);
    
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    
    // Simulate database connection and query execution
    int is_moderator = 1; // Assume user is a moderator for demonstration

    if (is_moderator) {
        char *result = "User is a moderator.\n";
        send(conn->fd, response, strlen(response), 0);
        send(conn->fd, result, strlen(result), 0);
    } else {
        char *result = "User is not a moderator.\n";
        send(conn->fd, response, strlen(response), 0);
        send(conn->fd, result, strlen(result), 0);
    }

    close(conn->fd);
}

void start_server() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    while (1) {
        connection conn;
        struct sockaddr_in client_address;
        socklen_t addrlen = sizeof(client_address);
        
        conn.fd = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
        if (conn.fd < 0) {
            perror("accept");
            continue;
        }

        handle_request(&conn);
    }

#ifdef _WIN32
    WSACleanup();
#endif
}

int main() {
    start_server();
    return 0;
}