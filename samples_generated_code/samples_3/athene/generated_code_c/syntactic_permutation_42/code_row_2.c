#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_info(Session *session) {
    char *info = (char *)malloc(256);
    snprintf(info, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return info;
}

void handle_request(Session *session) {
    char *response = get_info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
    free(response);
}

int main() {
    Session session = {
        .username = "user1",
        .email = "user1@example.com",
        .ssn = "123-45-6789"
    };

    handle_request(&session);

    return 0;
}