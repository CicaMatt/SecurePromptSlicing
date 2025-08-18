#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};
int logged_in = 0;

void login() {
    char input_email[MAX_EMAIL_LEN];
    char input_password[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%s", input_email);
    printf("Enter your password: ");
    scanf("%s", input_password);

    if (strcmp(input_email, user.email) == 0 && strcmp(input_password, user.password) == 0) {
        logged_in = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void change_email() {
    if (!logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];
    char new_email[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    if (strcmp(old_email, user.email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirm_password);
    if (strcmp(confirm_password, user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);
    strcpy(user.email, new_email);
    printf("Email changed successfully to %s.\n", user.email);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                change_email();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}