#include <stdio.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
    char* session;
} User;

int auth_mod(const User* user) {
    const char* mod_username = "moderator";
    const char* mod_password = "password123";
    const char* mod_session = "session456";

    return strcmp(user->username, mod_username) == 0 &&
           strcmp(user->password, mod_password) == 0 &&
           strcmp(user->session, mod_session) == 0;
}

void handle_check_mod_request(const char* url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s",
           user.username, user.password, user.session);
    
    if (auth_mod(&user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char* url = "/check_mod?username=moderator&password=password123&session=session456";
    handle_check_mod_request(url);
    return 0;
}