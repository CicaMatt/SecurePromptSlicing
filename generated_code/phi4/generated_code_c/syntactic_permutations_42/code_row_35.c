#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_KEY_USERNAME "username"
#define SESSION_KEY_EMAIL "email"
#define SESSION_KEY_SSN "ssn"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

const char* info(Session *session) {
    if (session && session->email && session->ssn) {
        static char response[256];
        snprintf(response, sizeof(response), "Username: %s; Email: %s; SSN: %s", 
                 session->username ? session->username : "", session->email, session->ssn);
        return response;
    }
    return "Session data not found";
}

void start_server() {
    Session user_session = {
        .username = "john_doe",
        .email = "john@example.com",
        .ssn = "123-45-6789"
    };

    char request[256] = "/info";

    if (strcmp(request, "/info") == 0) {
        printf("Response: %s\n", info(&user_session));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    start_server();
    return 0;
}