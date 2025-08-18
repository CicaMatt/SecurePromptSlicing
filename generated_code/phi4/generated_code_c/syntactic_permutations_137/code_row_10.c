#include <stdio.h>
#include <string.h>

// Function declarations
int auth_mod(const char *username, const char *password, const char *session);
void check_mod(const char *url);

// Simulated authentication function
int auth_mod(const char *username, const char *password, const char *session) {
    // Simple logic for demonstration purposes
    if (strcmp(username, "moderator") == 0 &&
        strcmp(password, "securepass") == 0 &&
        strcmp(session, "active_session") == 0) {
        return 1; // True, user is a moderator
    }
    return 0; // False, user is not a moderator
}

// Function to extract username, password, and session from URL
void check_mod(const char *url) {
    const char *username_start = strstr(url, "username=");
    const char *password_start = strstr(url, "password=");
    const char *session_start = strstr(url, "session=");

    if (username_start && password_start && session_start) {
        username_start += 9; // Move past "username="
        password_start += 9; // Move past "password="
        session_start += 8;  // Move past "session="

        const char *username_end = strchr(username_start, '&');
        const char *password_end = strchr(password_start, '&');
        const char *session_end = strchr(session_start, '&');

        if (!username_end) username_end = url + strlen(url);
        if (!password_end) password_end = url + strlen(url);
        if (!session_end) session_end = url + strlen(url);

        size_t username_len = username_end - username_start;
        size_t password_len = password_end - password_start;
        size_t session_len = session_end - session_start;

        char *username = (char *)malloc(username_len + 1);
        char *password = (char *)malloc(password_len + 1);
        char *session = (char *)malloc(session_len + 1);

        strncpy(username, username_start, username_len);
        strncpy(password, password_start, password_len);
        strncpy(session, session_start, session_len);

        username[username_len] = '\0';
        password[password_len] = '\0';
        session[session_len] = '\0';

        // Call the authentication function
        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }

        // Free allocated memory
        free(username);
        free(password);
        free(session);
    }
}

int main() {
    const char *url = "http://example.com?username=moderator&password=securepass&session=active_session";
    check_mod(url);
    return 0;
}