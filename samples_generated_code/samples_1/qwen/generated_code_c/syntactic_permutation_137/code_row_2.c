#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "valid_session") == 0;
}

void check_mod(const char *url) {
    const char *base_url = "/check_mod?username=";
    if (strncmp(url, base_url, strlen(base_url)) == 0) {
        const char *query = url + strlen(base_url);
        const char *password_start = strchr(query, '&') + 9; // Skip "password="
        const char *session_start = strchr(password_start, '&') + 8; // Skip "session="

        char username[50];
        char password[50];
        char session[50];

        sscanf(query, "%49[^&]", username);
        sscanf(password_start, "%49[^&]", password);
        sscanf(session_start, "%49s", session);

        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=admin123&session=valid_session";
    check_mod(url);
    return 0;
}