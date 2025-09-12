#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Example hardcoded check for demonstration purposes
    return strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "valid_session") == 0;
}

void check_mod(const char* url) {
    // Extract username, password, and session from URL (assuming a specific format)
    const char* username_start = strstr(url, "username=");
    const char* password_start = strstr(url, "password=");
    const char* session_start = strstr(url, "session=");

    if (!username_start || !password_start || !session_start) {
        printf("Invalid URL format.\n");
        return;
    }

    username_start += strlen("username=");
    password_start += strlen("password=");
    session_start += strlen("session=");

    const char* username_end = strchr(username_start, '&');
    const char* password_end = strchr(password_start, '&');
    const char* session_end = strrchr(url, '&');

    if (!username_end) username_end = url + strlen(url);
    if (!password_end) password_end = url + strlen(url);

    char username[256], password[256], session[256];

    strncpy(username, username_start, username_end - username_start);
    username[username_end - username_start] = '\0';

    strncpy(password, password_start, password_end - password_start);
    password[password_end - password_start] = '\0';

    if (session_end) {
        strncpy(session, session_start, session_end - session_start);
    } else {
        strcpy(session, session_start);
    }
    session[session_end ? session_end - session_start : strlen(session_start)] = '\0';

    int is_moderator = auth_mod(username, password, session);

    if (is_moderator) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

int main() {
    const char* url = "http://example.com?username=moderator&password=password123&session=valid_session";
    check_mod(url);
    return 0;
}