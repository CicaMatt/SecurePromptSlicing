#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_SESSION_LENGTH 100

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0 && strcmp(session, "valid_session") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char session[MAX_SESSION_LENGTH];

    // Dummy parsing logic for demonstration purposes
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=mod&password=pass&session=valid_session";
    check_mod(url);
    return 0;
}