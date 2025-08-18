#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 3

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session create_session(const char *username, const char *email, const char *ssn) {
    Session session;
    session.username = strdup(username);
    session.email = strdup(email);
    session.ssn = strdup(ssn);
    return session;
}

void free_session(Session *session) {
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn);
    }
}

void handle_info_request(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Information Page</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("</body></html>\n");
}

int main(void) {
    // Simulate session creation
    Session session = create_session("john_doe", "john@example.com", "123-45-6789");

    // Simulating a request to /info route
    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 &&
        strcmp(getenv("PATH_INFO"), "/info") == 0) {
        
        handle_info_request(&session);
    }

    free_session(&session);

    return 0;
}