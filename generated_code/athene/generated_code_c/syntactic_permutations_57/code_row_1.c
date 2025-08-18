#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASS_LEN];
    
    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password to change email: ");
    scanf("%49s", confirmPassword);
    if (authenticate(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    
    char inputPassword[MAX_PASS_LEN];
    printf("Enter your password to log in: ");
    scanf("%49s", inputPassword);
    
    if (authenticate(&user, user.email, inputPassword)) {
        printf("Logged in successfully.\n");
        change_email(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}