#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User user) {
    // Dummy authentication logic for demonstration
    return strcmp(user.username, "moderator") == 0 && 
           strcmp(user.password, "securepassword123") == 0 &&
           strcmp(user.session, "valid_session_token") == 0;
}

void handle_check_mod_request(char *url) {
    User user = {0};
    char *username, *password, *session;

    // Parse URL to extract username, password, and session
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", 
           user.username, user.password, user.session);

    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char url[] = "/check_mod?username=moderator&password=securepassword123&session=valid_session_token";
    handle_check_mod_request(url);
    return 0;
}