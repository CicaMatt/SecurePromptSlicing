#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

int is_logged_in = 1; // Assume the user is already logged in for simplicity
char current_email[MAX_EMAIL_LEN] = "user@example.com";
char password[MAX_PASSWORD_LEN] = "securepassword";

void change_email() {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%49s", old_email);

    printf("Enter your new email: ");
    scanf("%49s", new_email);

    if (strcmp(old_email, current_email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    if (strcmp(new_email, current_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%19s", confirm_password);

    if (strcmp(confirm_password, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(current_email, new_email);
    printf("Email successfully changed to %s\n", current_email);
}

int main() {
    change_email();
    return 0;
}