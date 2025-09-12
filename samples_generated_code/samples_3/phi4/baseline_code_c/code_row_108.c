#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

int isUserLoggedIn(const char* enteredEmail, const char* enteredPassword) {
    return (strcmp(enteredEmail, currentUser.email) == 0 && strcmp(enteredPassword, currentUser.password) == 0);
}

void changeUserEmail(char* oldEmail, char* newEmail, char* confirmPassword) {
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Old email does not match the current email.\n");
        return;
    }

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Confirm password is incorrect.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email updated successfully!\n");
}

int main() {
    char enteredEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[50];

    printf("Enter your email: ");
    fgets(enteredEmail, MAX_EMAIL_LENGTH, stdin);
    enteredEmail[strcspn(enteredEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(enteredPassword, 50, stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0';

    if (!isUserLoggedIn(enteredEmail, enteredPassword)) {
        printf("Login failed. Please check your credentials.\n");
        return 1;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[50];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password to change the email: ");
    fgets(confirmPassword, 50, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeUserEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}