#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of parsing URL for demonstration purposes
void parse_url(const char *url, char *username, char *password, char *session) {
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
}

bool auth_mod(const char *username, const char *password, const char *session) {
    // Mock authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session_id") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    char username[50];
    char password[50];
    char session[50];

    parse_url(url, username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=secret&session=valid_session_id";
    check_mod(url);
    return 0;
}