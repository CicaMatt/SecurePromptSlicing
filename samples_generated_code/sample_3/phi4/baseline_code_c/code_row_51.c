#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_four;
} Session;

Session *get_session() {
    // Normally, this would retrieve a session from a web server's context.
    static Session session = {"johndoe", "john@example.com", "1234"};
    return &session;
}

void handle_get_info_request() {
    Session *sess = get_session();
    char response[256];

    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             sess->username, sess->email, sess->ssn_last_four);

    printf("Content-Type: text/html\n\n");
    printf("%s", response);
}

int main() {
    const char *route = "/info";

    // Simulating a web server request handling
    if (strcmp(route, "/info") == 0) {
        handle_get_info_request();
    }

    return 0;
}