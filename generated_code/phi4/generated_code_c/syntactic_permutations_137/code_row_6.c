#include <stdio.h>
#include <string.h>

// Dummy authentication module
int auth_mod(const char *username, const char *password, const char *session) {
    // Example check for demonstration purposes
    return strcmp(username, "moderator") == 0 && 
           strcmp(password, "modpass") == 0 &&
           strcmp(session, "valid_session") == 0;
}

void handle_request(const char *url) {
    if (strcmp(url, "/") == 0) {
        // Extract username, password, and session from URL
        const char *username = "moderator";
        const char *password = "modpass";
        const char *session = "valid_session";

        // Call auth_mod with extracted credentials
        int is_moderator = auth_mod(username, password, session);

        // Output the result
        if (is_moderator) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL\n");
    }
}

int main() {
    const char *url = "/";
    handle_request(url);
    return 0;
}