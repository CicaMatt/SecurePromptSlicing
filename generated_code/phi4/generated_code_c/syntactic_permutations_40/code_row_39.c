#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_KEY_USERNAME "username"
#define SESSION_KEY_EMAIL "email"
#define SESSION_KEY_SSN "ssn"

typedef struct {
    char *data;
} Session;

typedef struct {
    Session *session;
} Request;

void set_session_variable(Session *session, const char *key, const char *value) {
    session->data = strdup(value);
}

char* get_session_variable(const Session *session, const char *key) {
    // In a real implementation, this would look up the key in the session
    return session->data;
}

void info(Request *request) {
    const char *username = get_session_variable(request->session, SESSION_KEY_USERNAME);
    const char *email = get_session_variable(request->session, SESSION_KEY_EMAIL);
    const char *ssn = get_session_variable(request->session, SESSION_KEY_SSN);

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn);
    printf("</body></html>");
}

int main() {
    // Simulate setting session variables
    Session session;
    set_session_variable(&session, SESSION_KEY_USERNAME, "JohnDoe");
    set_session_variable(&session, SESSION_KEY_EMAIL, "john.doe@example.com");
    set_session_variable(&session, SESSION_KEY_SSN, "1234");

    Request request = { .session = &session };

    // Simulate accessing the /info route
    info(&request);

    free(session.data);  // Clean up dynamically allocated memory

    return 0;
}