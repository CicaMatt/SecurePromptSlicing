#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

const char* info(Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return response;
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    const char *response = info(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);

    return 0;
}