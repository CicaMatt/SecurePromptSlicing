#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { "user123", "user@example.com", "123-45-6789" };

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n<head><title>Info Page</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    
    char last4ssn[5];
    strncpy(last4ssn, session.ssn + 6, 4);
    last4ssn[4] = '\0';
    
    printf("Username: %s<br>\n", session.username);
    printf("Email: %s<br>\n", session.email);
    printf("Last 4 digits of SSN: %s\n", last4ssn);

    printf("</body></html>\n");
}

int handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 21) == 0) {
        info();
        return 1;
    }
    return 0;
}

void run_server() {
    const int PORT = 8080;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    while ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_size))) {
        char buffer[1024] = {0};
        read(client_socket, buffer, 1023);

        if (!handle_request(buffer)) {
            printf("404 Not Found\n");
        }

        close(client_socket);
    }

    if (client_socket == -1) {
        perror("Accept failed");
    }

    close(server_socket);
}

int main() {
    run_server();
    return 0;
}


Note: This code assumes a Unix-like environment with networking capabilities and uses socket programming to create an HTTP server. It handles only the `/info` route for `GET` requests and returns basic HTML content. You need to compile it using `gcc -o webapp webapp.c` (assuming you save this code in `webapp.c`) and run the executable to start the server. Ensure that your development environment supports networking libraries, and appropriate permissions are granted to bind sockets on the specified port.