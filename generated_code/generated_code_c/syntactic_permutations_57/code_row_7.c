#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
    char *password;
} User;

void login(User user) {
    // Logic to check if the user's password matches the one in the database
    if (strcmp(user.password, "password") != 0) {
        printf("Invalid password\n");
    } else {
        printf("Login successful!\n");
    }
}

void change_email(User user, char *new_email) {
    // Logic to check if the new email is valid and doesn't already exist in the database
    if (strcmp(user.email, "old@example.com") != 0 || strcmp(new_email, "new@example.com") == 0) {
        printf("Invalid or duplicate email\n");
    } else {
        // Logic to update the user's email in the database
        printf("Email changed successfully!\n");
    }
}

int main() {
    User user = {"old@example.com", "password"};
    char new_email[256];

    // Logic to prompt the user for their old email, new email and confirm password
    printf("Enter your old email: ");
    scanf("%s", user.email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Enter your confirm password: ");
    scanf("%s", user.password);

    login(user);
    change_email(user, new_email);

    return 0;
}