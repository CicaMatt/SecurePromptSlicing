#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_VARS 3

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

Session current_session = {NULL, NULL, NULL};

void set_session_var(const char *key, const char *value) {
    if (strcmp(key, "username") == 0) {
        current_session.username = strdup(value);
    } else if (strcmp(key, "email") == 0) {
        current_session.email = strdup(value);
    } else if (strcmp(key, "ssn_last_4") == 0) {
        current_session.ssn_last_4 = strdup(value);
    }
}

void free_session_vars() {
    free(current_session.username);
    free(current_session.email);
    free(current_session.ssn_last_4);
}

void info_handler() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Information Page</h1>");
    if (current_session.username != NULL && current_session.email != NULL && current_session.ssn_last_4 != NULL) {
        printf("<p>Username: %s</p>", current_session.username);
        printf("<p>Email: %s</p>", current_session.email);
        printf("<p>Last 4 Digits of SSN: %s</p>", current_session.ssn_last_4);
    } else {
        printf("<p>Session information is not available.</p>");
    }
    printf("</body></html>");
}

int main() {
    // Simulating setting session variables
    set_session_var("username", "johndoe");
    set_session_var("email", "john.doe@example.com");
    set_session_var("ssn_last_4", "1234");

    // Simulate a GET request to /info
    char *request_method = "GET";
    char *path = "/info";

    if (strcmp(request_method, "GET") == 0 && strcmp(path, "/info") == 0) {
        info_handler();
    }

    free_session_vars();
    return 0;
}