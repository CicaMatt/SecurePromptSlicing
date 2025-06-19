#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 10
#define MAX_REQUEST_SIZE 512

struct session {
    char username[32];
};

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int handle_request(char *buf, struct session *session) {
    if (strncmp(buf, "GET /login HTTP/1.1", MAX_REQUEST_SIZE) == 0) {
        char username[32];
        char password[32];
        sscanf(buf, "GET /login?username=%[^&]&password=%s", username, password);
        
        if (do_login(username, password)) {
            session->username = strdup(username);
            return 1;
        } else {
            return 0;
        }
    } else if (strncmp(buf, "GET /secret HTTP/1.1", MAX_REQUEST_SIZE) == 0) {
        if (session->username != NULL && strcmp(session->username, "admin") == 0) {
            return 2;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(sockfd, BACKLOG);

    while (1) {
        int client_sockfd;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buf[MAX_REQUEST_SIZE];
        struct session *session = calloc(1, sizeof(struct session));

        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

        read(client_sockfd, buf, MAX_REQUEST_SIZE);

        int status;
        switch (handle_request(buf, session)) {
            case 1:
                status = "HTTP/1.1 302 Found\r\nLocation: /secret\r\n\r\n";
                break;
            case 2:
                status = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nSecret settings";
                break;
            default:
                status = "HTTP/1.1 403 Forbidden\r\n\r\n";
        }

        write(client_sockfd, status, strlen(status));

        close(client_sockfd);
    }

    return 0;
}