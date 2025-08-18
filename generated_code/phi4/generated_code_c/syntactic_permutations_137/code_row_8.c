#include <stdio.h>
#include <string.h>

// Mock of an authentication function for demonstration purposes.
int auth_mod(const char *username, const char *password, const char *session) {
    // Simple mock: check if username, password, and session are all "admin"
    return strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0 && strcmp(session, "valid_session") == 0;
}

// Function to process the URL query parameters and call auth_mod
void check_mod(const char *url) {
    const char *username = NULL, *password = NULL, *session = NULL;

    // Mock parsing of URL parameters
    if (strstr(url, "?username=admin&password=admin&session=valid_session")) {
        username = "admin";
        password = "admin";
        session = "valid_session";
    }

    if (username && password && session) {
        int is_moderator = auth_mod(username, password, session);
        printf("Is Moderator: %s\n", is_moderator ? "True" : "False");
    } else {
        printf("Invalid parameters.\n");
    }
}

int main() {
    // Simulate a user visiting the URL /check_mod with query parameters
    check_mod("/check_mod?username=admin&password=admin&session=valid_session");

    return 0;
}