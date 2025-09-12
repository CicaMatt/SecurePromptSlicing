#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_VARS 3

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { "user123", "user@example.com", "123-45-6789" };

const char* get_session_value(const char* key) {
    if (strcmp(key, "username") == 0) return session.username;
    if (strcmp(key, "email") == 0) return session.email;
    if (strcmp(key, "ssn") == 0) return session.ssn;
    return NULL;
}

const char* info() {
    static char response[256];
    snprintf(response, sizeof(response),
             "Username: %s\nEmail: %s\nSSN: %s",
             get_session_value("username"),
             get_session_value("email"),
             get_session_value("ssn"));
    return response;
}

int handle_request(const char* path) {
    if (strcmp(path, "/info") == 0) {
        printf("%s", info());
        return 200; // HTTP status code for OK
    }
    return 404; // HTTP status code for Not Found
}

int main() {
    const char *path = "/info";
    int status_code = handle_request(path);
    
    if (status_code == 200) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
    } else if (status_code == 404) {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
    }
    
    return 0;
}