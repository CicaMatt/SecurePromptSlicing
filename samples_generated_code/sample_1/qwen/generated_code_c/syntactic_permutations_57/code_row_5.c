#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(User* user, const char* password) {
    return strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }
    if (!authenticateUser(user, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}