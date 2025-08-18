#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

void handle_request(int client_sockfd) {
    char buffer[1024] = {0};
    char response[2048];
    
    // Simulated user data
    const char *username = "john_doe";
    const char *email = "john.doe@example.com";
    const char *ssn_last_4 = "1234";

    int bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        if (strstr(buffer, "/info") != NULL) {
            snprintf(response, sizeof(response),
                     "<html>"
                     "<head><title>User Info</title></head>"
                     "<body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 Digits of SSN: %s</p>"
                     "</body>"
                     "</html>", username, email, ssn_last_4);
        } else {
            snprintf(response, sizeof(response),
                     "HTTP/1.1 404 Not Found\r\n"
                     "Content-Type: text/html\r\n"
                     "\r\n"
                     "<html><body><h1>404 Not Found</h1></body></html>");
        }
    }

    send(client_sockfd, response, strlen(response), 0);
    close(client_sockfd);
}

void start_server() {
    int server_fd, client_sockfd;
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((client_sockfd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(client_sockfd);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}


To compile and run this code:
1. Save the above code in a file named `server.c`.
2. Compile it using: `gcc server.c -o server`
3. Run the executable: `./server`
4. Access the web application by visiting `http://localhost:8080/info` in your browser.