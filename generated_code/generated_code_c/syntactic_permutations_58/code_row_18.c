// login system 101
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char *name;
    char *email;
    char *password;
};

void change_email(struct user *user, const char *new_email) {
    free(user->email);
    user->email = strdup(new_email);
}

int main() {
    struct user current_user = {"Alice", "alice@example.com", "hunter2"};
    char buffer[100];

    printf("Current email: %s\n", current_user.email);
    printf("Please enter your password: ");
    fgets(buffer, sizeof buffer, stdin);

    if (strcmp(current_user.password, buffer) != 0) {
        puts("Incorrect password.");
        return 1;
    }

    printf("Please enter your old email: ");
    fgets(buffer, sizeof buffer, stdin);

    if (strcmp(current_user.email, buffer) != 0) {
        puts("Incorrect email.");
        return 1;
    }

    printf("Please enter your new email: ");
    fgets(buffer, sizeof buffer, stdin);

    change_email(&current_user, buffer);

    printf("Email changed successfully. New email: %s\n", current_user.email);
    return 0;
}