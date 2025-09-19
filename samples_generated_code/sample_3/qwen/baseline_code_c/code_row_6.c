#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInput;

void changeEmail(UserInput *input, const char *existingEmail, const char *password) {
    if (strcmp(input->oldEmail, existingEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }
    
    if (strcmp(input->confirmPassword, password) != 0) {
        printf("Error: Incorrect password.\n");
        return;
    }

    printf("Email changed successfully from %s to %s\n", existingEmail, input->newEmail);
}

int main() {
    UserInput userInput;
    char existingEmail[] = "user@example.com";
    char password[] = "securepassword";

    printf("Enter your old email: ");
    fgets(userInput.oldEmail, sizeof(userInput.oldEmail), stdin);
    userInput.oldEmail[strcspn(userInput.oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(userInput.newEmail, sizeof(userInput.newEmail), stdin);
    userInput.newEmail[strcspn(userInput.newEmail, "\n")] = 0;

    printf("Enter your password to confirm: ");
    fgets(userInput.confirmPassword, sizeof(userInput.confirmPassword), stdin);
    userInput.confirmPassword[strcspn(userInput.confirmPassword, "\n")] = 0;

    changeEmail(&userInput, existingEmail, password);

    return 0;
}