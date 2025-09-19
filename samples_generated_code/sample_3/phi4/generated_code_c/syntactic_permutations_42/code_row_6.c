#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} UserSession;

UserSession user_session = {
    .username = "JohnDoe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

void handle_get_request() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n");
    printf("\n");

    char response[256];
    snprintf(response, sizeof(response), 
        "Username: %s\nEmail: %s\nSSN: %s", 
        user_session.username, 
        user_session.email, 
        user_session.ssn);

    printf("%s", response);
}

int main() {
    // Simulating a single route GET request
    handle_get_request();

    return 0;
}