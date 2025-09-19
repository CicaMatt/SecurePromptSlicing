#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
}

Session *create_session(const char *username, const char *email, const char *ssn) {
    Session *session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
    return session;
}

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", (int)strlen(session->ssn) > 4 ? 4 : (int)strlen(session->ssn), session->ssn + strlen(session->ssn) - 4);
    printf("</body></html>");
}

void handle_request() {
    char *username = getenv("SESSION_USERNAME");
    char *email = getenv("SESSION_EMAIL");
    char *ssn = getenv("SESSION_SSN");

    if (username == NULL || email == NULL || ssn == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Session not found</h1></body></html>");
        return;
    }

    Session *session = create_session(username, email, ssn);
    info(session);
    free_session(session);
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method != NULL && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info != NULL && strcmp(path_info, "/info") == 0) {
            handle_request();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><h1>404 Not Found</h1></body></html>");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Method not allowed</h1></body></html>");
    }
    return 0;
}