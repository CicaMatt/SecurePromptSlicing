#include <stdio.h>
#include <string.h>

int auth_mod(const char *name, const char *password, const char *session) {
    // Simple mock authentication logic for demonstration purposes.
    if (strcmp(name, "moderator") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "valid_session") == 0) {
        return 1; // true
    }
    return 0; // false
}

void check_mod(const char *name, const char *password, const char *session) {
    if (auth_mod(name, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example usage of check_mod
    const char *name = "moderator";
    const char *password = "modpass";
    const char *session = "valid_session";

    check_mod(name, password, session);

    return 0;
}