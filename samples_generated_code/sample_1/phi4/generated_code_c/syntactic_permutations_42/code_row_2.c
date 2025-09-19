#include <stdio.h>
#include <string.h>

#define MAX_SESSION_VARS 3

typedef struct {
    char key[MAX_SESSION_VARS][50];
    char value[MAX_SESSION_VARS][100];
} Session;

Session session = {
    .key = {"username", "email", "ssn"},
    .value = {"john_doe", "john.doe@example.com", "123-45-6789"}
};

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("Content-Type: text/plain\n\n");
        printf("Email: %s\nSSN: %s\n", session.value[1], session.value[2]);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char request_path[100];

    // Simulate receiving a GET request for the /info route
    strcpy(request_path, "/info");

    handle_request(request_path);

    return 0;
}