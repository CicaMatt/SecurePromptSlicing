#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_SESSION_LEN 50

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0 && strcmp(session, "valid_session") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    char session[MAX_SESSION_LEN + 1];

    // Parsing the URL for username, password, and session
    sscanf(url, "/check_mod?username=%50[^&]&password=%50[^&]&session=%50s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=admin123&session=valid_session";
    check_mod(url);
    return 0;
}