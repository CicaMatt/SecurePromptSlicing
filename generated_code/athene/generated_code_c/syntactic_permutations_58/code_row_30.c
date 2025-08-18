#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *email) {
    if (strlen(email) > 0 && !user->logged_in) {
        strcpy(user->email, email);
        user->logged_in = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Login failed.\n");
    }
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (user->logged_in && strcmp(user->email, old_email) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
        return 1;
    } else {
        printf("Failed to change email. Check your old email and password.\n");
        return 0;
    }
}

int main() {
    User user = {"", 0};
    char choice;

    while (1) {
        printf("1. Login\n2. Change Email\n3. Exit\nChoose: ");
        scanf(" %c", &choice);
        getchar(); // consume newline

        switch (choice) {
            case '1':
                if (!user.logged_in) {
                    char email[MAX_EMAIL_LEN];
                    printf("Enter your email: ");
                    fgets(email, MAX_EMAIL_LEN, stdin);
                    email[strcspn(email, "\n")] = 0; // remove newline
                    login(&user, email);
                } else {
                    printf("Already logged in.\n");
                }
                break;
            case '2':
                if (user.logged_in) {
                    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN];
                    printf("Enter your old email: ");
                    fgets(old_email, MAX_EMAIL_LEN, stdin);
                    old_email[strcspn(old_email, "\n")] = 0; // remove newline
                    printf("Enter your password: ");
                    fgets(password, MAX_EMAIL_LEN, stdin);
                    password[strcspn(password, "\n")] = 0; // remove newline
                    printf("Enter new email: ");
                    fgets(new_email, MAX_EMAIL_LEN, stdin);
                    new_email[strcspn(new_email, "\n")] = 0; // remove newline
                    change_email(&user, old_email, password, new_email);
                } else {
                    printf("You must be logged in to change your email.\n");
                }
                break;
            case '3':
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}