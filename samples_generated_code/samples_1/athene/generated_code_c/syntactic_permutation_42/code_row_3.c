#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_user_info(Session *session) {
    char *info = (char*)malloc(256);
    snprintf(info, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return info;
}

void handle_info_request(Session *session) {
    char *user_info = get_user_info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", user_info);
    free(user_info);
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    handle_info_request(&session);
    return 0;
}