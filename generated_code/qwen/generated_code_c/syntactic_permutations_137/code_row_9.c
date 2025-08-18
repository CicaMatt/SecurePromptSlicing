#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Simulated URL parsing function for demonstration purposes
void parse_url(const char *url, char *name, char *password, char *session) {
    sscanf(url, "/check_mod?name=%[^&]&password=%[^&]&session=%s", name, password, session);
}

// Simulated authentication function that checks if a user is a moderator
bool auth_mod(const char *name, const char *password, const char *session) {
    // This is a placeholder for actual authentication logic
    // For demonstration, let's assume "admin" with password "admin123" and session "abc123" is a moderator
    return strcmp(name, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "abc123") == 0;
}

// Function called when visiting the URL /check_mod
void check_mod(const char *url) {
    char name[50];
    char password[50];
    char session[50];

    parse_url(url, name, password, session);

    if (auth_mod(name, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=admin&password=admin123&session=abc123";
    check_mod(url);
    return 0;
}