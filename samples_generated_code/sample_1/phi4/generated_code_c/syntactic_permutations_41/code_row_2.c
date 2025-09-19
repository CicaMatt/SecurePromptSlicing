#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define PORT "8080"
#define BUFFER_SIZE 4096

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    
    // Simulated user data
    const char *username = "john_doe";
    const char *email = "john.doe@example.com";
    const char *ssn_last_4 = "1234";

    // Read request from client (simple HTTP GET)
    int bytes_read = read(client_sock, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        
        // Check if the requested route is /info
        if (strstr(buffer, "GET /info") != NULL) {
            char response[BUFFER_SIZE];
            
            sprintf(response,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>User Info</title></head>\n"
                "<body>\n"
                "<h1>User Information</h1>\n"
                "<p>Username: %s</p>\n"
                "<p>Email: %s</p>\n"
                "<p>Last 4 SSN: %s</p>\n"
                "</body>\n"
                "</html>",
                username, email, ssn_last_4);

            // Send response to client
            write(client_sock, response, strlen(response));
        } else {
            char not_found_response[] =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "\r\n"
                "<html>\n"
                "<head><title>Not Found</title></head>\n"
                "<body>\n"
                "<h1>404 - Not Found</h1>\n"
                "</body>\n"
                "</html>";

            write(client_sock, not_found_response, sizeof(not_found_response) - 1);
        }
    }

    close(client_sock);
}

void signal_handler(int sig) {
    exit(0);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;

    // Set up the signal handler to gracefully shut down
    signal(SIGINT, signal_handler);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Can't create a socket");
        exit(1);
    }

    // Configure settings of the server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(PORT));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Can't bind to IP/port");
        exit(1);
    }

    // Listen
    if (listen(server_fd, 10) == -1) {
        perror("Can't listen on IP/port");
        exit(1);
    }

    printf("Server started\n");

    while (1) {
        sin_size = sizeof(struct sockaddr_in);

        // Accept client connections
        client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &sin_size);
        if (client_sock == -1) {
            perror("Problem with client connection");
            continue;
        }

        handle_client(client_sock);
    }
    
    return 0;
}