#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session session = {"JohnDoe", "john.doe@example.com", "123-45-6789"};

const char* info() {
    static char response[300];
    snprintf(response, sizeof(response), 
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    return response;
}

void handle_request(const char *request) {
    if (strcmp(request, "/info") == 0) {
        printf("%s", info());
    } else {
        printf("404 Not Found");
    }
}

int main() {
    const char *requests[] = {"/info", "/unknown"};
    
    for (size_t i = 0; i < sizeof(requests)/sizeof(requests[0]); ++i) {
        handle_request(requests[i]);
        printf("\n---\n");
    }

    return 0;
}