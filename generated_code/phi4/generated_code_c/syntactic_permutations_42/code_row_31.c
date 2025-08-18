#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} UserSession;

UserSession session;

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        info();
    }
}

void info() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", session.username);
    printf("Email: %s\n", session.email);
    printf("SSN: %s\n", session.ssn);
}

int main() {
    // Simulate setting session data
    strcpy(session.username, "JohnDoe");
    strcpy(session.email, "john.doe@example.com");
    strcpy(session.ssn, "123-45-6789");

    char request[100];
    
    printf("Enter HTTP request: ");
    fgets(request, sizeof(request), stdin);
    
    handle_request(request);

    return 0;
}