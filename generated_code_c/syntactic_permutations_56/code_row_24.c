#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct User {
    char* email;
    char* password;
};

void change_email(struct User *user, const char* new_email) {
    if (strcmp(user->password, "qwerty") != 0) {
        printf("Invalid password. Try again.\n");
        return;
    }

    if (strcmp(new_email, user->email) == 0) {
        printf("New email can't be same as old email.\n");
        return;
    }

    free(user->email);
    user->email = strdup(new_email);
}

int main() {
    struct User user = {"john.doe@example.com", "qwerty"};

    change_email(&user, "jane.doe@example.com");

    printf("User email is now: %s\n", user.email);

    return 0;
}