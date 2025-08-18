#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(char *username, char *password, char *session) {
    return 1; // Always returns true for this example
}

void check_mod(User *user) {
    int result = auth_mod(user->username, user->password, user->session);
    if (result) {
        printf("Authentication successful\n");
    } else {
        printf("Authentication failed\n");
    }
}

int main() {
    User user = {
        .username = "testuser",
        .password = "testpass",
        .session = "testsession"
    };

    check_mod(&user);

    return 0;
}