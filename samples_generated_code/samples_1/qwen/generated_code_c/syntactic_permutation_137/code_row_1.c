#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of parsing URL parameters
void parse_url_params(const char *url, char *name, char *password, char *session) {
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);
}

// Mock implementation of auth_mod function
bool auth_mod(const char *name, const char *password, const char *session) {
    // Dummy check for moderator credentials
    return strcmp(name, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "valid_session") == 0;
}

void check_mod(const char *url) {
    char name[50], password[50], session[50];
    parse_url_params(url, name, password, session);
    if (auth_mod(name, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=admin&password=admin123&session=valid_session";
    check_mod(url);
    return 0;
}