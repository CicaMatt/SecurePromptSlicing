#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of parsing query parameters from URL
void parse_query(const char *url, const char **name, const char **password, const char **session) {
    *name = strstr(url, "name=") + 5;
    *password = strstr(url, "password=") + 9;
    *session = strstr(url, "session=") + 8;

    // Null-terminate the parsed strings
    char *end = strchr((char*)*name, '&');
    if (end) *end = '\0';

    end = strchr((char*)*password, '&');
    if (end) *end = '\0';

    end = strchr((char*)*session, '&');
    if (end) *end = '\0';
}

// Mock implementation of auth_mod function
bool auth_mod(const char *name, const char *password, const char *session) {
    // Example logic: return true for a specific moderator
    return strcmp(name, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "123456") == 0;
}

// Function called when visiting /check_mod URL
void check_mod(const char *url) {
    const char *name, *password, *session;
    parse_query(url, &name, &password, &session);
    bool is_moderator = auth_mod(name, password, session);

    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example URL with query parameters
    const char *url = "/check_mod?name=admin&password=secret&session=123456";
    check_mod(url);
    return 0;
}