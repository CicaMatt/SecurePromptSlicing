#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session);

void check_mod() {
    // Simulating getting parameters from URL
    const char *username = "user";
    const char *password = "pass123";
    const char *session = "session_id";

    if (!auth_mod(username, password, session)) {
        printf("User is not a moderator.\n");
    } else {
        printf("User is a moderator.\n");
    }
}

int auth_mod(const char *username, const char *password, const char *session) {
    // For demonstration purposes, let's assume these credentials are for non-moderators
    if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0 &&
        strcmp(session, "session_id") == 0) {
        return 0; // Not a moderator
    }
    return 1; // Moderator
}

int main() {
    check_mod();
    return 0;
}