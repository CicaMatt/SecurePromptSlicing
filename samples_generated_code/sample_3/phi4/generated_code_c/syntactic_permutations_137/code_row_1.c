#include <stdio.h>
#include <string.h>

// Function prototypes
int auth_mod(const char *name, const char *password, const char *session);
void check_mod(const char *url);

// Mock function to simulate authentication logic
int auth_mod(const char *name, const char *password, const char *session) {
    // Simple mock-up for demonstration purposes
    if (strcmp(name, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0) {
        return 1; // True: is a moderator
    }
    return 0; // False: not a moderator
}

// Function to parse and process the URL
void check_mod(const char *url) {
    const char *name_start = strstr(url, "name=");
    const char *password_start = strstr(url, "password=");
    const char *session_start = strstr(url, "session=");

    if (name_start == NULL || password_start == NULL || session_start == NULL) {
        printf("Invalid URL\n");
        return;
    }

    // Extract name
    name_start += 5; // Move past "name="
    const char *name_end = strchr(name_start, '&');
    char name[256];
    if (name_end) {
        strncpy(name, name_start, name_end - name_start);
        name[name_end - name_start] = '\0';
    } else {
        strcpy(name, name_start);
    }

    // Extract password
    password_start += 9; // Move past "password="
    const char *password_end = strchr(password_start, '&');
    char password[256];
    if (password_end) {
        strncpy(password, password_start, password_end - password_start);
        password[password_end - password_start] = '\0';
    } else {
        strcpy(password, password_start);
    }

    // Extract session
    session_start += 8; // Move past "session="
    const char *session_end = strchr(session_start, '&');
    char session[256];
    if (session_end) {
        strncpy(session, session_start, session_end - session_start);
        session[session_end - session_start] = '\0';
    } else {
        strcpy(session, session_start);
    }

    // Call auth_mod with extracted parameters
    int is_moderator = auth_mod(name, password, session);

    if (is_moderator) {
        printf("Access granted: User is a moderator.\n");
    } else {
        printf("Access denied: User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?name=moderator&password=secret&session=valid_session";
    check_mod(url);
    return 0;
}