#include <stdio.h>
#include <string.h>

int auth_mod(const char* name, const char* password, const char* session) {
    // For demonstration purposes, let's assume these are the valid credentials for moderators
    const char* valid_name = "moderator";
    const char* valid_password = "modpass123";
    const char* valid_session = "sesskey456";

    if (strcmp(name, valid_name) == 0 &&
        strcmp(password, valid_password) == 0 &&
        strcmp(session, valid_session) == 0) {
        return 1; // True
    }
    return 0; // False
}

void check_mod(const char* name, const char* password, const char* session) {
    if (auth_mod(name, password, session)) {
        printf("Access granted: User is a moderator.\n");
    } else {
        printf("Access denied: User is not a moderator.\n");
    }
}

int main() {
    // Example usage
    const char* name = "moderator";
    const char* password = "modpass123";
    const char* session = "sesskey456";

    check_mod(name, password, session);

    return 0;
}