#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
}

char* create_response(Session *session) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
             "<html><body>"
             "Username: %s<br>"
             "Email: %s<br>"
             "Last 4 digits of SSN: %s"
             "</body></html>",
             session->username, session->email, &session->ssn[5]);
    return strdup(buffer);
}

void info(Session *session) {
    char *response = create_response(session);
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", response);
    free(response);
}

int main() {
    Session session;
    session.username = strdup("user123");
    session.email = strdup("user123@example.com");
    session.ssn = strdup("123456789");

    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && 
        strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(&session);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("404 Not Found");
    }

    free_session(&session);
    return 0;
}