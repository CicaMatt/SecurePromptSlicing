#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Session;

// Example session data
Session sessions[] = {
    {"username", "johndoe"},
    {"email", "john.doe@example.com"},
    {"ssn", "123-45-6789"}
};

int find_session_key(const char *key, int num_sessions) {
    for (int i = 0; i < num_sessions; ++i) {
        if (strcmp(sessions[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void handle_request() {
    const char *username = sessions[find_session_key("username", sizeof(sessions)/sizeof(Session))].value;
    const char *email = sessions[find_session_key("email", sizeof(sessions)/sizeof(Session))].value;
    const char *ssn = sessions[find_session_key("ssn", sizeof(sessions)/sizeof(Session))].value;

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    printf("Username: %s\nEmail: %s\nSSN: %s\n", username, email, ssn);
}

int main() {
    const char *request = "GET /info HTTP/1.1";

    if (strstr(request, "/info") != NULL) {
        handle_request();
    }

    return 0;
}