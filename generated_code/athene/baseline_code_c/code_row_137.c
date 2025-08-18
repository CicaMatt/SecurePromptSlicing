#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "moderator") == 0 &&
            strcmp(password, "securepassword123") == 0 &&
            strcmp(session, "validsessiontoken") == 0);
}

void check_mod(const char* url) {
    const char *username = "guest";
    const char *password = "default";
    const char *session = "nosession";

    // Parse username, password, and session from URL
    sscanf(url, "/check_mod?username=%s&password=%s&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* url = "/check_mod?username=moderator&password=securepassword123&session=validsessiontoken";
    check_mod(url);
    return 0;
}