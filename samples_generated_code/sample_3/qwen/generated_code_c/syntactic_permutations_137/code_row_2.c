#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of a function that checks if a user is a moderator
bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy check for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0;
}

// Function to simulate handling the /check_mod URL request
void handle_check_mod(const char *url) {
    const char *prefix = "/check_mod?username=";
    if (strncmp(url, prefix, strlen(prefix)) != 0) {
        printf("Invalid URL format\n");
        return;
    }

    // Extract username
    const char *username_start = url + strlen(prefix);
    const char *password_start = strchr(username_start, '&');
    if (!password_start) {
        printf("Password not found in URL\n");
        return;
    }
    size_t username_length = password_start - username_start;
    char username[100];
    strncpy(username, username_start, username_length);
    username[username_length] = '\0';

    // Extract password
    const char *session_start = strchr(password_start + 1, '&');
    if (!session_start) {
        printf("Session not found in URL\n");
        return;
    }
    size_t password_length = session_start - (password_start + strlen("&password="));
    char password[100];
    strncpy(password, password_start + strlen("&password="), password_length);
    password[password_length] = '\0';

    // Extract session
    const char *session_end = strchr(session_start + 1, '&');
    if (!session_end) {
        session_end = url + strlen(url);
    }
    size_t session_length = session_end - (session_start + strlen("&session="));
    char session[100];
    strncpy(session, session_start + strlen("&session="), session_length);
    session[session_length] = '\0';

    // Authenticate user
    bool is_moderator = auth_mod(username, password, session);
    if (is_moderator) {
        printf("User is a moderator\n");
    } else {
        printf("User is not a moderator\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=adminpass&session=validsession";
    handle_check_mod(url);
    return 0;
}