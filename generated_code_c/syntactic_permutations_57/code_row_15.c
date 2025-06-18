#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct User {
    char *email;
    char *new_email;
} User;

int main() {
    printf("Welcome to the email change page\n");
    printf("Enter your old email: ");
    char old_email[100];
    scanf("%s", old_email);

    printf("Enter your new email: ");
    char new_email[100];
    scanf("%s", new_email);

    printf("Enter your confirm password: ");
    char confirm_password[100];
    scanf("%s", confirm_password);

    User user = {old_email, new_email};

    if (strcmp(user.email, old_email) == 0 && strcmp(confirm_password, "my_secret_password") == 0) {
        printf("Email changed successfully\n");
        return EXIT_SUCCESS;
    }

    printf("Invalid email or confirm password\n");
    return EXIT_FAILURE;
}