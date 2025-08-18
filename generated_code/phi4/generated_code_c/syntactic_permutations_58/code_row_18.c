#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

void login(User *user) {
    printf("Enter your old email: ");
    char oldEmail[MAX_EMAIL_LENGTH];
    scanf("%s", oldEmail);
    
    printf("Confirm your password: ");
    char password[PASSWORD_LENGTH];
    scanf("%s", password);

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        printf("Login successful. You can change your email.\n");

        printf("Enter new email: ");
        char newEmail[MAX_EMAIL_LENGTH];
        scanf("%s", newEmail);

        strcpy(user->email, newEmail);
        printf("Email changed to %s successfully!\n", user->email);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};

    // Simulating a login process
    login(&user);

    return 0;
}