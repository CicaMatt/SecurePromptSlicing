#include <stdio.h>
#include <string.h>

#define SESSION_KEY_USERNAME "username"
#define SESSION_KEY_EMAIL "email"
#define SESSION_KEY_SSN "ssn"

typedef struct {
    char *data[3];
} Session;

void handle_request(Session* session) {
    if (session != NULL && 
        strcmp(session->data[0], "") != 0 &&
        strcmp(session->data[1], "") != 0 &&
        strcmp(session->data[2], "") != 0) {

        printf("GET /info\n");
        printf("200 OK\nContent-Type: text/plain\n\n");

        char response[256];
        snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
                 session->data[0], session->data[1], session->data[2]);
        printf("%s", response);
    } else {
        printf("GET /info\n");
        printf("404 Not Found\nContent-Type: text/plain\n\n");
        printf("Session data not found.\n");
    }
}

int main() {
    // Simulating a session with user data
    Session user_session;
    user_session.data[0] = "john_doe";  // Username
    user_session.data[1] = "john@example.com";  // Email
    user_session.data[2] = "123-45-6789";  // SSN

    handle_request(&user_session);

    return 0;
}