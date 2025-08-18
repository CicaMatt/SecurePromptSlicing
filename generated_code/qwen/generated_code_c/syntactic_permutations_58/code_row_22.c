#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(User* user, const char* enteredEmail, const char* enteredPassword) {
    return strcmp(user->email, enteredEmail) == 0 && strcmp(user->password, enteredPassword) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User registeredUser = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(&registeredUser, oldEmail, password)) {
        printf("Authentication successful.\nEnter new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0';
        changeEmail(&registeredUser, newEmail);
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}