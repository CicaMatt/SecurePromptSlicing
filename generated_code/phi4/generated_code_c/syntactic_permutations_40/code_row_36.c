#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *data[3];
} Session;

Session session = {{"user123", "user@example.com", "123-45-6789"}};

void handle_request(char *path) {
    if (strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[1024];
    
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>Personal Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>SSN: %s</p>"
             "</body></html>",
             session.data[0], session.data[1], session.data[2]);

    printf("Content-Type: text/html\n\n");
    printf("%s", response);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}