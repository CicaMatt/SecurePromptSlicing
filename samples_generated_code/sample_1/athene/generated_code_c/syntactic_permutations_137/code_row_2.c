#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "modpass") == 0 && strcmp(session, "valid_session") == 0) {
        return 1;
    }
    return 0;
}

void handle_check_mod(const char *url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", user.username, user.password, user.session);
    if (auth_mod(user.username, user.password, user.session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=mod&password=modpass&session=valid_session";
    handle_check_mod(url);
    return 0;
}