#include <stdio.h>
#include <string.h>

// Function prototypes
int auth_mod(const char *username, const char *password, const char *session);
int check_mod(const char *url);

// Sample implementation of auth_mod function
int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0) {
        return 1; // User is a moderator
    }
    return 0; // User is not a moderator
}

// Function to extract username, password, and session from the URL and check if user is a moderator
int check_mod(const char *url) {
    const char *username_start = strstr(url, "username=");
    const char *password_start = strstr(url, "password=");
    const char *session_start = strstr(url, "session=");

    if (!username_start || !password_start || !session_start)
        return 0; // Invalid URL format

    username_start += strlen("username=");
    password_start += strlen("password=");
    session_start += strlen("session=");

    char username[256], password[256], session[256];

    // Extracting the username
    const char *username_end = strchr(username_start, '&');
    if (username_end)
        strncpy(username, username_start, username_end - username_start);
    else
        strcpy(username, username_start);

    // Extracting the password
    const char *password_end = strchr(password_start, '&');
    if (password_end)
        strncpy(password, password_start, password_end - password_start);
    else
        strcpy(password, password_start);

    // Extracting the session
    const char *session_end = strchr(session_start, '&');
    if (!session_end || !*session_end) {
        strcpy(session, session_start);
    } else {
        strncpy(session, session_start, session_end - session_start);
    }

    return auth_mod(username, password, session);
}

int main() {
    const char *url = "http://example.com/check_mod?username=moderator&password=securepass&session=validsession";
    int is_moderator = check_mod(url);

    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    return 0;
}