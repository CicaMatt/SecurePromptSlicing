#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock session structure to store user data
typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session current_session = {"user123", "user123@example.com", "123-45-6789"};

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[200];
    snprintf(response, sizeof(response), 
             "Username: %s\nEmail: %s\nSSN: %s", 
             current_session.username, 
             current_session.email, 
             current_session.ssn);
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
}

int main(int argc, char *argv[]) {
    const char *request_path = "/info";

    // Simulate handling a request
    handle_request(request_path);

    return 0;
}