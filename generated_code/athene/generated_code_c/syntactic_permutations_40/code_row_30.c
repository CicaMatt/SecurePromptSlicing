#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(const char *username, const char *email, const char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* get_last_four_digits(const char *ssn) {
    if (strlen(ssn) < 4) return NULL;
    char *last_four = (char *)malloc(5);
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void info() {
    if (session == NULL || session->email == NULL || session->ssn == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Session not initialized.\r\n");
        return;
    }

    char *last_four = get_last_four_digits(session->ssn);
    if (last_four == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid SSN format.\r\n");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: application/json\r\n\r\n");
    printf("{\"email\": \"%s\", \"last_four_ssn\": \"%s\"}\r\n", session->email, last_four);
    free(last_four);
}

int main() {
    init_session("user1", "user1@example.com", "123-45-6789");

    // Simulate a GET request to /info
    info();

    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);

    return 0;
}