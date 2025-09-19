#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { "john_doe", "john@example.com", "123-45-6789" };

void info() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", session.username);
    printf("Email: %s\n", session.email);
    printf("SSN: %s\n", session.ssn);
}

int main(int argc, char *argv[]) {
    char method[10];
    char path[100];

    // Simulate a request
    strcpy(method, "GET");
    strcpy(path, "/info");

    if (strcmp(method, "GET") == 0 && strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }

    return 0;
}