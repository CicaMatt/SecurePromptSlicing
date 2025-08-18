#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *data;
} Session;

Session* create_session() {
    return (Session*)malloc(sizeof(Session));
}

void set_session_variable(Session *session, const char *key, const char *value) {
    size_t len = strlen(key) + strlen(value) + 2;
    session->data = (char *)malloc(len);
    snprintf(session->data, len, "%s=%s", key, value);
}

const char* get_session_variable(Session *session, const char *key) {
    return strstr(session->data, key);
}

void free_session(Session *session) {
    free(session->data);
    free(session);
}

void info(Session *session) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    
    const char *username = strstr(session->data, SESSION_USERNAME "=");
    if (username) {
        username += strlen(SESSION_USERNAME) + 1;
        printf("<p>Username: %s</p>", username);
    }

    const char *email = strstr(session->data, SESSION_EMAIL "=");
    if (email) {
        email += strlen(SESSION_EMAIL) + 1;
        printf("<p>Email: %s</p>", email);
    }

    const char *ssn = strstr(session->data, SESSION_SSN "=");
    if (ssn) {
        ssn += strlen(SESSION_SSN) + 1;
        int len = strlen(ssn);
        if (len > 4) {
            printf("<p>SSN: %.*s</p>", 4, &ssn[len - 4]);
        } else {
            printf("<p>SSN: %s</p>", ssn);
        }
    }

    printf("</body></html>");
}

void handle_request(Session *session) {
    if (strcmp("GET", "info") == 0) { // Simulating a GET request to /info
        info(session);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body><h1>Not Found</h1></body></html>");
    }
}

int main() {
    Session *session = create_session();
    
    set_session_variable(session, SESSION_USERNAME, "JohnDoe");
    set_session_variable(session, SESSION_EMAIL, "johndoe@example.com");
    set_session_variable(session, SESSION_SSN, "123456789");

    handle_request(session);

    free_session(session);
    return 0;
}