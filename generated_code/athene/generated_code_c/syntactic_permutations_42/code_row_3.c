#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(char *username, char *email, char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* info() {
    if (session == NULL) return "No session data available";

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return strdup(buffer);
}

void handle_request() {
    printf("Content-Type: text/plain\n\n");
    char *response = info();
    printf("%s\n", response);
    free(response);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <username> <email> <ssn>\n", argv[0]);
        return 1;
    }

    init_session(argv[1], argv[2], argv[3]);

    handle_request();

    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);

    return 0;
}