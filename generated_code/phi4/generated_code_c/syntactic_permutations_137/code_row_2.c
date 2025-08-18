#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy check for demonstration purposes
    if (strcmp(username, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "active_session") == 0) {
        return 1; // true: user is a moderator
    }
    return 0; // false: user is not a moderator
}

void check_mod(const char *username, const char *password, const char *session) {
    int result = auth_mod(username, password, session);
    if (result) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulate calling check_mod when user visits /check_mod
    const char *username = "moderator";
    const char *password = "secret";
    const char *session = "active_session";

    check_mod(username, password, session);

    return 0;
}