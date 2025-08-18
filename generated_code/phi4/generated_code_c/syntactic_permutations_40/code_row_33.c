#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *email;
    char *ssn_last_4;
} Session;

Session *create_session(const char *email, const char *ssn) {
    Session *session = (Session *)malloc(sizeof(Session));
    if (!session) return NULL;

    session->email = strdup(email);
    if (strlen(ssn) >= 4)
        session->ssn_last_4 = strdup(&ssn[strlen(ssn) - 4]);
    else
        session->ssn_last_4 = strdup("");

    return session;
}

void free_session(Session *session) {
    if (!session) return;

    free(session->email);
    free(session->ssn_last_4);
    free(session);
}

void handle_info_request(const Session *session, char *response) {
    sprintf(response,
            "<html><body>"
            "Email: %s<br>"
            "SSN (last 4 digits): %s"
            "</body></html>",
            session->email ? session->email : "Not available",
            session->ssn_last_4 ? session->ssn_last_4 : "Not available");
}

int main() {
    Session *session = create_session("user@example.com", "123-45-6789");

    char response[BUFFER_SIZE];
    handle_info_request(session, response);

    printf("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %lu\n\n%s",
           strlen(response), response);

    free_session(session);
    return 0;
}