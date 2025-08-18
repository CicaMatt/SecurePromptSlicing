#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define MAX_PASSWORD_LENGTH 64

typedef struct {
    char email[MAX_EMAIL_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
} User;

int is_logged_in = 0;
User user = {"example@example.com", "password123"};

void change_email() {
    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char new_email[MAX_EMAIL_LENGTH + 1];
    char confirm_password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter new email: ");
    scanf("%254s", new_email);
    printf("Confirm password: ");
    scanf("%64s", confirm_password);

    if (strcmp(confirm_password, user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user.email, new_email);
    printf("Email changed successfully to %s.\n", user.email);
}

int main() {
    // Simulate login
    is_logged_in = 1;

    change_email();

    return 0;
}