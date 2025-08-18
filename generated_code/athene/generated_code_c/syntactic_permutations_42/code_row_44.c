#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User user = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    char *response = malloc(200);
    sprintf(response, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", user.username, user.email, user.ssn);
    return response;
}

void handle_request(char *path) {
    if (strcmp(path, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n%s", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found");
    }
}

int main() {
    char *request = "/info";
    handle_request(request);
    return 0;
}