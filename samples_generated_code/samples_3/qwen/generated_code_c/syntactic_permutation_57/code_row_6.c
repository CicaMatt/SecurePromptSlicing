#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(User user, const char* password) {
    return strcmp(user.password, password) == 0;
}

void changeEmail(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }
    if (!authenticateUser(*user, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}