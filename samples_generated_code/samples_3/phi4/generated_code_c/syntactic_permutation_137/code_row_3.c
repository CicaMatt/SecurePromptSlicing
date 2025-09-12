#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Simple hardcoded check for demonstration purposes
    return strcmp(username, "moderator") == 0 && 
           strcmp(password, "password123") == 0 &&
           strcmp(session, "valid_session") == 0;
}

void check_mod(const char* username, const char* password, const char* session) {
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulate URL parameters
    const char* username = "moderator";
    const char* password = "password123";
    const char* session = "valid_session";

    check_mod(username, password, session);

    return 0;
}