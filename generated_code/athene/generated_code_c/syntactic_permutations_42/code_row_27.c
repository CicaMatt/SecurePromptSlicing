#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_user_info(Session *session) {
    char *info = malloc(256);
    snprintf(info, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return info;
}

void handle_request(void (*callback)(Session *)) {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    char *response = get_user_info(&session);
    callback(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
    free(response);
}

int main() {
    handle_request(get_user_info);
    return 0;
}