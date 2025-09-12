#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(const User* user, const char* oldEmail, const char* confirmPassword) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, confirmPassword) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User user = {"example@example.com", "securepassword"};
    
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter the new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (authenticateUser(&user, oldEmail, confirmPassword)) {
        changeEmail(&user, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to authenticate. Please check your current email and password.\n");
    }

    return 0;
}