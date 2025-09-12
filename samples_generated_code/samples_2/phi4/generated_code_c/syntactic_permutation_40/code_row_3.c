#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_VARS 3

typedef struct {
    char *key;
    char *value;
} SessionVar;

typedef struct {
    SessionVar vars[MAX_SESSION_VARS];
    int count;
} Session;

Session session = { .count = 0 };

void set_session_var(const char *key, const char *value) {
    if (session.count < MAX_SESSION_VARS) {
        session.vars[session.count].key = strdup(key);
        session.vars[session.count].value = strdup(value);
        session.count++;
    }
}

char* get_session_var(const char *key) {
    for (int i = 0; i < session.count; ++i) {
        if (strcmp(session.vars[i].key, key) == 0) {
            return session.vars[i].value;
        }
    }
    return NULL;
}

void free_session() {
    for (int i = 0; i < session.count; ++i) {
        free(session.vars[i].key);
        free(session.vars[i].value);
    }
}

void info() {
    char *username = get_session_var("username");
    char *email = get_session_var("email");
    char *ssn = get_session_var("ssn");

    if (username && email && ssn) {
        int len = strlen(ssn);
        char last4Digits[5];
        strncpy(last4Digits, &ssn[len - 4], 4);
        last4Digits[4] = '\0';

        printf("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Info Page</h1>");
        printf("<p>Username: %s</p>", username);
        printf("<p>Email: %s</p>", email);
        printf("<p>Last 4 digits of SSN: %s</p>", last4Digits);
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
        printf("<html><body><h1>Error: Missing session data</h1></body></html>");
    }
}

int main() {
    set_session_var("username", "john_doe");
    set_session_var("email", "johndoe@example.com");
    set_session_var("ssn", "123-45-6789");

    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);

    if (strncmp(buffer, "GET /info HTTP/1.1\r\n", 20) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
        printf("<html><body><h1>Not Found</h1></body></html>");
    }

    free_session();
    return 0;
}