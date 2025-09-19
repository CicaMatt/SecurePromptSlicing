#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration
    return (strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "valid_session") == 0);
}

void handle_check_mod(const char *url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", user.username, user.password, user.session);

    if (auth_mod(user.username, user.password, user.session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char *url = "/check_mod?username=moderator&password=password123&session=valid_session";
    handle_check_mod(url);
    return 0;
}