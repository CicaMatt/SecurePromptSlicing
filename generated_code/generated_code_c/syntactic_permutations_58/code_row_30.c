#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *username;
    char *email;
    char *password;
};

void change_email(struct User *user, const char *new_email) {
    if (strcmp(user->email, new_email) != 0) {
        user->email = malloc(strlen(new_email) + 1);
        strcpy(user->email, new_email);
    }
}

int main() {
    struct User user;
    char buffer[256];
    char *old_email;
    char *password;

    printf("Enter your username: ");
    scanf("%s", buffer);
    user.username = malloc(strlen(buffer) + 1);
    strcpy(user.username, buffer);

    printf("Enter your email: ");
    scanf("%s", buffer);
    user.email = malloc(strlen(buffer) + 1);
    strcpy(user.email, buffer);

    printf("Enter your password: ");
    scanf("%s", buffer);
    user.password = malloc(strlen(buffer) + 1);
    strcpy(user.password, buffer);

    old_email = user.email;

    printf("Enter your new email: ");
    scanf("%s", buffer);

    if (strcmp(old_email, buffer) == 0 && strcmp(user.password, buffer) == 0) {
        change_email(&user, buffer);
    } else {
        printf("Email not changed!");
    }

    return 0;
}