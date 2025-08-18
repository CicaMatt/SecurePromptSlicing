#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *email;
    char *ssn_last_4;
} Session;

Session current_session = {0};

void set_session(const char *email, const char *ssn) {
    if (current_session.email != NULL) free(current_session.email);
    if (current_session.ssn_last_4 != NULL) free(current_session.ssn_last_4);

    size_t email_len = strlen(email);
    size_t ssn_len = strlen(ssn);

    current_session.email = malloc(email_len + 1);
    strcpy(current_session.email, email);

    current_session.ssn_last_4 = malloc(5); // 4 digits + null terminator
    strncpy(current_session.ssn_last_4, &ssn[ssn_len - 4], 4);
    current_session.ssn_last_4[4] = '\0';
}

void free_session() {
    if (current_session.email != NULL) free(current_session.email);
    if (current_session.ssn_last_4 != NULL) free(current_session.ssn_last_4);

    current_session.email = NULL;
    current_session.ssn_last_4 = NULL;
}

const char* info() {
    static char response[BUFFER_SIZE];
    snprintf(response, sizeof(response),
             "Username: %s\nEmail: %s\nLast 4 digits of SSN: %s",
             "example_user", current_session.email, current_session.ssn_last_4);
    return response;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        printf("%s", info());
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        printf("Route not found.");
    }
}

int main() {
    // Simulate setting session variables
    set_session("user@example.com", "123456789");

    // Simulate web server handling requests
    const char *path = "/info";  // This would be dynamically determined in a real server

    handle_request(path);

    free_session();
    return 0;
}