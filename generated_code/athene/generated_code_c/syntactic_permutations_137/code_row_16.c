#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    char session[100];
} User;

int auth_mod(const char *username, const char *password, const char *session) {
    // Mock moderator credentials and session for demonstration
    const char *mod_username = "mod";
    const char *mod_password = "modpass";
    const char *valid_session = "valid-session-id";

    return strcmp(username, mod_username) == 0 &&
           strcmp(password, mod_password) == 0 &&
           strcmp(session, valid_session) == 0;
}

int check_mod(User *user) {
    return auth_mod(user->username, user->password, user->session);
}

int main() {
    User user = {"mod", "modpass", "valid-session-id"};
    if (check_mod(&user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
    return 0;
}