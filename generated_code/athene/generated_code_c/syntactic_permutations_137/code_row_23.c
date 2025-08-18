#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int is_moderator(User user) {
    // Dummy implementation for demonstration
    if (strcmp(user.username, "mod") == 0 && strcmp(user.password, "modpass") == 0 && strcmp(user.session, "valid_session") == 0) {
        return 1;
    }
    return 0;
}

void check_mod(char *url) {
    char username[256], password[256], session[256];
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);

    User user = { .username = username, .password = password, .session = session };

    if (is_moderator(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example URL
    char url[] = "/check_mod?username=mod&password=modpass&session=valid_session";
    check_mod(url);
    return 0;
}