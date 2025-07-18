#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_details {
    char *email;
};

int check_user(char *email, struct user_details *user) {
    if (strcmp(email, user->email) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int change_email(char *new_email, char *old_password, struct user_details *user) {
    if (check_user(old_password, user)) {
        user->email = new_email;
        printf("Email changed to %s", new_email);
        return 1;
    }
    else {
        printf("Incorrect old email or password");
        return 0;
    }
}

void main() {
    struct user_details user = {"test@example.com"};
    char *new_email = "newtest@example.com";
    char *old_password = "123456";
    if (change_email(new_email, old_password, &user)) {
        printf("Email changed");
    }
    else {
        printf("Incorrect old email or password");
    }
}