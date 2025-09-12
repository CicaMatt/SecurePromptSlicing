#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request() {
    Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    char *response = info(&session);
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("%s\n", response);
}

int main() {
    handle_request();
    return 0;
}