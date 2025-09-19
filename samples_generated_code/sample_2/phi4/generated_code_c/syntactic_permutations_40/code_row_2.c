#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

const User user = {"johndoe", "john.doe@example.com", "123-45-6789"};

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>User Information</h1>");
        printf("<p>Username: %s</p>", user.username);
        printf("<p>Email: %s</p>", user.email);
        printf("<p>Last 4 digits of SSN: %c%c%c%c</p>",
               user.ssn[6], user.ssn[7], user.ssn[8], user.ssn[9]);
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        read(new_socket, buffer, sizeof(buffer));
        handle_request(buffer);
        
        close(new_socket);
    }

    return 0;
}