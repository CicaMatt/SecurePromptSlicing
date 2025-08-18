#include <stdio.h>
#include <string.h>

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for example purposes
    const char *mod_username = "admin";
    const char *mod_password = "password123";
    const char *mod_session = "session456";

    return (strcmp(username, mod_username) == 0 &&
            strcmp(password, mod_password) == 0 &&
            strcmp(session, mod_session) == 0);
}

void check_mod(const char* url) {
    char username[100];
    char password[100];
    char session[100];

    // Dummy URL parsing for example purposes
    sscanf(url, "?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "?username=admin&password=password123&session=session456";
    check_mod(url);
    return 0;
}