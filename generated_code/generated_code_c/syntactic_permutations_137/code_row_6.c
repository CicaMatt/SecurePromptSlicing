#include <stdio.h>

bool auth_mod(char *username, char *password, int session) {
    return false;
}

void handler() {
    char username[1024];
    char password[1024];
    int session = 0;

    scanf("%s", username);
    scanf("%s", password);
    scanf("%d", &session);

    if (auth_mod(username, password, session)) {
        printf("Hello Moderator");
    } else {
        printf("You are not a moderator");
    }
}