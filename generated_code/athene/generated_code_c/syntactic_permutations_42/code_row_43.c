#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User user = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    static char response[100];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", user.username, user.email, user.ssn);
    return response;
}

int handle_request(char *route) {
    if (strcmp(route, "/info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", info());
        return 0;
    }
    printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found\n");
    return 1;
}

int main() {
    char *request = "/info"; // Simulate a GET request to /info
    handle_request(request);
    return 0;
}