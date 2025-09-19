#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_KEY_USERNAME "username"
#define SESSION_KEY_EMAIL "email"
#define SESSION_KEY_SSN "ssn"

typedef struct {
    char *data[3];
} Session;

Session create_session() {
    Session session;
    session.data[0] = malloc(20);
    session.data[1] = malloc(50);
    session.data[2] = malloc(15);

    strcpy(session.data[0], "user123");
    strcpy(session.data[1], "user123@example.com");
    strcpy(session.data[2], "123-45-6789");

    return session;
}

void destroy_session(Session *session) {
    free(session->data[0]);
    free(session->data[1]);
    free(session->data[2]);
}

char* get_session_info(Session *session) {
    char *info = malloc(150);
    snprintf(info, 150, "Username: %s\nEmail: %s\nSSN: %s", session->data[0], session->data[1], session->data[2]);
    return info;
}

void handle_request(const char* route) {
    if (strcmp(route, "/info") == 0) {
        Session session = create_session();
        char *response = get_session_info(&session);
        printf("%s\n", response);
        free(response);
        destroy_session(&session);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char* route = "/info"; // Simulate accessing the route
    handle_request(route);
    return 0;
}