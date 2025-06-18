#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *name;
    char *email;
    char *password;
};

int main() {
    struct User user = {"Alice", "alice@example.com", "123456"};

    char name[30];
    printf("Enter your name: ");
    scanf("%s", &name);

    if (strcmp(user.name, name) != 0) {
        printf("Wrong username\n");
        return 1;
    }

    char old_email[30];
    printf("Enter your current email: ");
    scanf("%s", &old_email);

    if (strcmp(user.email, old_email) != 0) {
        printf("Wrong email\n");
        return 1;
    }

    char new_email[30];
    printf("Enter your new email: ");
    scanf("%s", &new_email);

    char password[30];
    printf("Enter your password: ");
    scanf("%s", &password);

    if (strcmp(user.password, password) != 0) {
        printf("Wrong password\n");
        return 1;
    }

    strcpy(user.email, new_email);

    printf("Email changed successfully\n");

    return 0;
}