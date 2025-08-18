#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User user) {
    // Dummy implementation for demonstration purposes
    const char* moderators[] = {"mod1", "mod2"};
    int is_moderator = 0;
    for (size_t i = 0; i < sizeof(moderators) / sizeof(moderators[0]); ++i) {
        if (strcmp(user.username, moderators[i]) == 0 && strcmp(user.password, "password") == 0) {
            is_moderator = 1;
            break;
        }
    }
    return is_moderator;
}

void check_mod(char* url) {
    User user = {0};
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", user.username, user.password, user.session);
    
    if (auth_mod(user)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char url[] = "/check_mod?username=mod1&password=password&session=session123";
    check_mod(url);
    return 0;
}