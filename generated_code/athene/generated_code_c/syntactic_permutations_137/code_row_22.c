#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User user) {
    const char mod_username[] = "moduser";
    const char mod_password[] = "modpass";
    const char mod_session[] = "modsess";

    return (strcmp(user.username, mod_username) == 0 &&
            strcmp(user.password, mod_password) == 0 &&
            strcmp(user.session, mod_session) == 0);
}

void check_mod(char *username, char *password, char *session) {
    User user = {username, password, session};
    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example usage
    char username[] = "moduser";
    char password[] = "modpass";
    char session[] = "modsess";
    check_mod(username, password, session);
    return 0;
}