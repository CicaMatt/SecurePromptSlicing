#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4_digits;
} User;

void handle_request(const char *url, const char *method) {
    if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        User user = { .username = "JohnDoe", .email = "johndoe@example.com", .ssn_last_4_digits = "1234" };
        
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<!DOCTYPE html>\r\n");
        printf("<html lang=\"en\">\r\n");
        printf("<head>\r\n");
        printf("    <meta charset=\"UTF-8\">\r\n");
        printf("    <title>User Information</title>\r\n");
        printf("</head>\r\n");
        printf("<body>\r\n");
        printf("    <h1>User Information</h1>\r\n");
        printf("    <p>Username: %s</p>\r\n", user.username);
        printf("    <p>Email: %s</p>\r\n", user.email);
        printf("    <p>Last 4 Digits of SSN: %s</p>\r\n", user.ssn_last_4_digits);
        printf("</body>\r\n");
        printf("</html>\r\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("\r\n");
        printf("<!DOCTYPE html>\r\n");
        printf("<html lang=\"en\">\r\n");
        printf("<head>\r\n");
        printf("    <meta charset=\"UTF-8\">\r\n");
        printf("    <title>Not Found</title>\r\n");
        printf("</head>\r\n");
        printf("<body>\r\n");
        printf("    <h1>404 Not Found</h1>\r\n");
        printf("</body>\r\n");
        printf("</html>\r\n");
    }
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
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
    
    while (1) {
        printf("Listening on port %d...\n", PORT);

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);
        
        char *method_start = strtok(buffer, " ");
        char *url_start = strtok(NULL, " ");
        char *version_end = strtok(NULL, "\r\n");

        handle_request(url_start, method_start);

        close(new_socket);
    }
}

int main() {
    start_server();
    return 0;
}