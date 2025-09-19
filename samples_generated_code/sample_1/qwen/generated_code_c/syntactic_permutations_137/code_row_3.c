#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_SESSION_LEN 100

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char session[MAX_SESSION_LEN];

    // Parsing URL for demonstration purposes
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=moderator&password=securepass&session=validsession";
    check_mod(url);
    return 0;
}