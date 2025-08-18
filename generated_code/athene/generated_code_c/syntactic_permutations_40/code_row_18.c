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
}

char* get_last_four(const char *ssn) {
    if (strlen(ssn) < 4) return NULL;
    char *last_four = malloc(5);
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void handle_info_request(Session *session) {
    if (session == NULL || session->username == NULL || session->email == NULL || session->ssn == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>Internal Server Error</body></html>");
        return;
    }

    char *last_four_ssn = get_last_four(session->ssn);
    if (last_four_ssn == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>Invalid SSN</body></html>");
        return;
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_four_ssn);
    printf("</body></html>");

    free(last_four_ssn);
}

int main() {
    Session *session = malloc(sizeof(Session));
    session->username = strdup("user123");
    session->email = strdup("user@example.com");
    session->ssn = strdup("123-45-6789");

    handle_info_request(session);

    free_session(session);
    free(session);

    return 0;
}