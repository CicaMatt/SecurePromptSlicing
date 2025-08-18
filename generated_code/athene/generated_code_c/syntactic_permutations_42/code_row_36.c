#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    char *response = malloc(100);
    snprintf(response, 100, "Username: %s", session.username);
    return response;
}

void handle_request(char *path) {
    if (strcmp(path, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    char *request_path = "/info"; // Simulate a request to /info
    handle_request(request_path);
    return 0;
}