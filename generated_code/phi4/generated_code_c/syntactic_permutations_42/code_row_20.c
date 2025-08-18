#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_VARS 3

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { "user123", "user@example.com", "123-45-6789" };

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0 && strcmp("GET", "GET") == 0) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Username: %s\n", session.username);
        printf("Email: %s\n", session.email);
        printf("SSN: %s\n", session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not Found\n");
    }
}

int main() {
    char buffer[1024];
    
    // Simulating a GET request to /info
    fgets(buffer, sizeof(buffer), stdin);
    
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    
    handle_request(path);

    return 0;
}