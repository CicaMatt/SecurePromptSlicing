#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *email;
    char *password;
};

void change_email(struct User user, char *new_email) {
    if (user.email == NULL || new_email == NULL) {
        printf("Invalid email or password\n");
        return;
    }

    if (strcmp(user.email, "example@example.com") != 0) {
        printf("User is not logged in\n");
        return;
    }

    if (strcmp(user.password, "pass12345") != 0) {
        printf("Password does not match\n");
        return;
    }

    user.email = new_email;
    printf("Email changed to %s\n", user.email);
}

int main() {
    struct User user = {"example@example.com", "pass12345"};

    char *new_email = (char *)malloc(sizeof(char) * 64);
    strcpy(new_email, "test@example.com");

    change_email(user, new_email);

    free(new_email);

    return 0;
}