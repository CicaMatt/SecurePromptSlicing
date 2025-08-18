#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "moderator") == 0 && strcmp(password, "securepassword123") == 0 && strcmp(session, "validsessiontoken") == 0);
}

int check_mod(const char *url) {
    const char *username = NULL;
    const char *password = NULL;
    const char *session = NULL;

    // Parse URL for username, password, and session
    username = strstr(url, "username=");
    if (username != NULL) {
        username += 9; // Length of "username="
        password = strstr(username, "&password=");
        if (password != NULL) {
            *password = '\0';
            password += 10; // Length of "&password="
            session = strstr(password, "&session=");
            if (session != NULL) {
                *session = '\0';
                session += 9; // Length of "&session="
            }
        }
    }

    if (username && password && session) {
        return auth_mod(username, password, session);
    }

    return 0;
}

int main() {
    const char *url = "http://example.com/check_mod?username=moderator&password=securepassword123&session=validsessiontoken";
    if (check_mod(url)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
    return 0;
}