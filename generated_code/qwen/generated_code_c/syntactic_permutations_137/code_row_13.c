#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "valid_session") == 0;
}

void check_mod(const char *username, const char *password, const char *session) {
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulating URL parameters
    const char *username = "admin";
    const char *password = "admin123";
    const char *session = "valid_session";

    check_mod(username, password, session);

    return 0;
}