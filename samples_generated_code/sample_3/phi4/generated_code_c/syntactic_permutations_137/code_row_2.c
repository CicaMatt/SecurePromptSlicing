#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Simple check for demonstration purposes
    if (strcmp(username, "moderator") == 0 && strcmp(password, "pass1234") == 0 && strcmp(session, "active_session") == 0) {
        return 1; // true
    }
    return 0; // false
}

void handle_request(const char *url) {
    if (strcmp(url, "/check_mod") == 0) {
        const char *username = "moderator"; // Example username extracted from URL
        const char *password = "pass1234";   // Example password extracted from URL
        const char *session = "active_session"; // Example session token extracted from URL

        int is_moderator = auth_mod(username, password, session);
        if (is_moderator) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }
}

int main() {
    const char *url = "/check_mod";
    handle_request(url);
    return 0;
}