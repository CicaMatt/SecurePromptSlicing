#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {"user123", "user@example.com", "123-45-6789"};

char* info() {
    char *response = malloc(200);
    snprintf(response, 200, "Username: %s, Email: %s, SSN: %s", session.username, session.email, session.ssn);
    return response;
}

void handle_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found\n");
    }
}

int main() {
    const char *route = "/info"; // Simulate a GET request to /info
    handle_request(route);
    return 0;
}