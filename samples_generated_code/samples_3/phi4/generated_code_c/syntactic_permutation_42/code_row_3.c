#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[256];
    char email[256];
    char ssn[11];
} Session;

Session session = {"user123", "user@example.com", "123-45-6789"};

const char* info() {
    static char response[SESSION_SIZE];
    snprintf(response, SESSION_SIZE, 
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    return response;
}

void handle_request(const char *request_path) {
    if (strcmp(request_path, "/info") == 0) {
        printf("%s", info());
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *test_path = "/info";
    handle_request(test_path);
    return 0;
}