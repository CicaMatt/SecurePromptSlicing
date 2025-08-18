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
    if (strcmp(username, "moderator") == 0 && strcmp(password, "secure_password") == 0 && strcmp(session, "valid_session_token") == 0) {
        return 1;
    }
    return 0;
}

void check_mod(const char *url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", user.username, user.password, user.session);
    
    int is_mod = auth_mod(user.username, user.password, user.session);
    
    if (is_mod) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char *url = "/check_mod?username=moderator&password=secure_password&session=valid_session_token";
    check_mod(url);
    return 0;
}