#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

Session sessionData = {"example_user", "user@example.com", "123-45-6789"};

void handle_request(const char *request) {
    if (strcmp(request, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[200];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             sessionData.username, sessionData.email, sessionData.ssn);
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
}

int main() {
    char request[MAX_SESSION_SIZE];
    
    // Simulate reading a GET request
    printf("Enter the request path (e.g., /info): ");
    fgets(request, sizeof(request), stdin);

    // Remove newline character if present
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n') {
        request[len - 1] = '\0';
    }

    handle_request(request);

    return 0;
}