#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    char input_email[MAX_EMAIL_LENGTH], input_password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", input_email);
    printf("Enter your password: ");
    scanf("%s", input_password);

    if (strcmp(input_email, user->email) == 0 && strcmp(input_password, user->password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
        return;
    }

    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    if (strcmp(old_email, user->email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);

    printf("Confirm your password to change the email: ");
    scanf("%s", confirm_password);
    if (strcmp(confirm_password, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "securepassword123"};

    login(&user);

    printf("Your current email is: %s\n", user.email);

    return 0;
}