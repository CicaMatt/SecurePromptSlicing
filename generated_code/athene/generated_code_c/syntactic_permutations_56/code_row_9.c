#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char username[50];
    char password[MAX_PASSWORD_LEN] = "securepassword";
    char logged_in_user[50] = "user123";
    char current_email[MAX_EMAIL_LEN] = "user@example.com";
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    if (strcmp(username, logged_in_user) != 0) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%s", old_email);
    if (strcmp(old_email, current_email) != 0) {
        printf("Old email does not match the current email.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", new_email);
    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%s", confirm_password);
    if (strcmp(confirm_password, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(current_email, new_email);
    printf("Email successfully changed to %s\n", current_email);

    return 0;
}