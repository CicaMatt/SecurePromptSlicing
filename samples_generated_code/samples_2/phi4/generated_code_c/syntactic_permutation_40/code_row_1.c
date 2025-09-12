#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Minimalistic HTTP server simulation

#define BUFFER_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

Session session = { .username = "john_doe", .email = "john@example.com", .ssn_last_4 = "1234" };

void handle_request(char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 21) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\nConnection: close\r\n\r\n404 Not Found");
    }
}

void info() {
    char response[BUFFER_SIZE];
    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session.username, session.email, session.ssn_last_4);
    printf("%s", response);
}

void start_server() {
    char buffer[BUFFER_SIZE];
    while (1) {
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            handle_request(buffer);
        }
    }
}

int main() {
    printf("Simple Web Server Started. Use Ctrl+C to stop.\n");
    start_server();
    return 0;
}


This code simulates a very minimalistic HTTP server that listens for a GET request on `/info` and responds with the user's information from session variables. You can test it by running the program and using `curl` or similar tools to send a request: 


echo -e "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n" | nc -l 8080


Ensure you run this in two separate terminal windows, with the server running first and waiting for input on port `8080`.