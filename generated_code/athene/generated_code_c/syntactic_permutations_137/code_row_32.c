#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "moderator") != 0;
}

void check_mod() {
    char username[100], password[100], session[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter session: ");
    scanf("%99s", session);

    if (auth_mod(username, password, session)) {
        printf("User is not a moderator.\n");
    } else {
        printf("User is a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}