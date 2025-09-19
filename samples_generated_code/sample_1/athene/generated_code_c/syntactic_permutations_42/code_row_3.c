#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_user_info(Session *session) {
    int len = snprintf(NULL, 0, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    char *response = malloc(len + 1);
    if (response == NULL) exit(1);
    snprintf(response, len + 1, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_info_request(Session *session) {
    char *user_info = get_user_info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", user_info);
    free(user_info);
}

int main() {
    Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    handle_info_request(&session);
    return 0;
}