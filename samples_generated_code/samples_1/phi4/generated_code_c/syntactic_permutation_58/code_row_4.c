#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

void login(User *user, char *username, char *password) {
    if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }
}

void changeEmail(User *user, char *old_email, char *new_email, char *password) {
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Old email or password incorrect. Email not changed.\n");
    }
}

int main() {
    User user = {"user123", "old@example.com", "password123"};

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(&user, username, password);

    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[50];
    printf("Enter your current email to verify: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);
    printf("Enter new email: ");
    scanf("%s", new_email);

    changeEmail(&user, old_email, new_email, confirm_password);

    return 0;
}