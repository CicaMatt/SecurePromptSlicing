#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int logged_in;
} User;

void login(User *user, const char *email) {
    strcpy(user->email, email);
    user->logged_in = 1;
}

int change_email(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->logged_in) return 0;
    if (strcmp(user->email, oldEmail) != 0 || strcmp(password, PASSWORD) != 0) return 0;
    strcpy(user->email, newEmail);
    return 1;
}

int main() {
    User user = {"", 0};
    
    char email[MAX_EMAIL_LENGTH], oldEmail[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    
    printf("Enter your email to log in: ");
    scanf("%99s", email);
    login(&user, email);

    if (user.logged_in) {
        printf("Logged in successfully.\n");
        
        printf("Enter old email: ");
        scanf("%99s", oldEmail);
        printf("Enter password: ");
        scanf("%99s", password);
        printf("Enter new email: ");
        scanf("%99s", newEmail);

        if (change_email(&user, oldEmail, password, newEmail)) {
            printf("Email changed successfully to %s.\n", user.email);
        } else {
            printf("Failed to change email. Incorrect old email or password.\n");
        }
    } else {
        printf("Login failed.\n");
    }

    return 0;
}