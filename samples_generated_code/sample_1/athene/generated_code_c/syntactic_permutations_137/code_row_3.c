#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(username, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0) {
        return 1;
    }
    return 0;
}

void check_mod(const char *url) {
    char username[100], password[100], session[100];
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    User user = { .username = username, .password = password, .session = session };
    if (auth_mod(user.username, user.password, user.session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=moderator&password=secret&session=valid_session";
    check_mod(url);
    return 0;
}