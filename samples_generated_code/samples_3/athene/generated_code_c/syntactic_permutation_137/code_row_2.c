#include <stdio.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
    char* session;
} User;

int auth_mod(User user) {
    const char *mod_username = "admin";
    const char *mod_password = "123456";
    const char *mod_session = "session123";

    return (strcmp(user.username, mod_username) == 0 &&
            strcmp(user.password, mod_password) == 0 &&
            strcmp(user.session, mod_session) == 0);
}

void check_mod(char* url) {
    User user;
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", user.username, user.password, user.session);

    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char url[] = "/check_mod?username=admin&password=123456&session=session123";
    check_mod(url);
    return 0;
}