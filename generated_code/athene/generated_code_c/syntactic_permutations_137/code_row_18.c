#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User user) {
    // Example moderator credentials (insecure, for demonstration only)
    const char *mod_username = "admin";
    const char *mod_password = "123456";
    const char *mod_session = "abcd1234";

    return strcmp(user.username, mod_username) == 0 &&
           strcmp(user.password, mod_password) == 0 &&
           strcmp(user.session, mod_session) == 0;
}

void handle_check_mod(const char *url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", 
           user.username, user.password, user.session);

    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char *url = "/check_mod?username=admin&password=123456&session=abcd1234";
    handle_check_mod(url);
    return 0;
}