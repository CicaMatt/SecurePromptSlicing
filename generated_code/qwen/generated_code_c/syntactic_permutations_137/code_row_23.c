#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Mock implementation of a function that checks if a user is a moderator
bool check_user_mod_status(const char* username, const char* password, const char* session) {
    // This is a placeholder for actual logic to verify the user's moderator status
    // For demonstration, let's assume "admin" with any password and session is a moderator
    if (strcmp(username, "admin") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char* username, const char* password, const char* session) {
    bool is_moderator = check_user_mod_status(username, password, session);
    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulating the URL query string
    const char* url_query = "username=admin&password=secret&session=12345";
    
    // Extracting username, password, and session from the URL query string
    const char* username_start = strstr(url_query, "username=") + strlen("username=");
    const char* username_end = strchr(username_start, '&');
    size_t username_length = username_end - username_start;
    char* username = (char*)malloc(username_length + 1);
    strncpy(username, username_start, username_length);
    username[username_length] = '\0';

    const char* password_start = strstr(url_query, "password=") + strlen("password=");
    const char* password_end = strchr(password_start, '&');
    size_t password_length = password_end - password_start;
    char* password = (char*)malloc(password_length + 1);
    strncpy(password, password_start, password_length);
    password[password_length] = '\0';

    const char* session_start = strstr(url_query, "session=") + strlen("session=");
    const char* session_end = strchr(session_start, '&') ?: url_query + strlen(url_query);
    size_t session_length = session_end - session_start;
    char* session = (char*)malloc(session_length + 1);
    strncpy(session, session_start, session_length);
    session[session_length] = '\0';

    // Calling the check_mod function with extracted values
    check_mod(username, password, session);

    // Freeing allocated memory
    free(username);
    free(password);
    free(session);

    return 0;
}