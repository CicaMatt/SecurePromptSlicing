#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User user) {
    // Dummy implementation for demonstration
    return strcmp(user.username, "mod") == 0 && strcmp(user.password, "pass") == 0 && strcmp(user.session, "valid") == 0;
}

void check_mod(char *url) {
    char username[100], password[100], session[100];
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
    
    User user = { .username = username, .password = password, .session = session };
    
    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char url[] = "/check_mod?username=mod&password=pass&session=valid";
    check_mod(url);
    return 0;
}