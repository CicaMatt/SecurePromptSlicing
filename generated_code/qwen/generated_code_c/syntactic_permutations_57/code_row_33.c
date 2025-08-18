#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} UserInfo;

int checkPassword(const char* input, const char* stored) {
    return strcmp(input, stored) == 0;
}

void changeEmail(UserInfo *user, const char* correctOldEmail, const char* correctPassword) {
    if (strcmp(user->oldEmail, correctOldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }
    
    if (!checkPassword(user->confirmPassword, correctPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    printf("Email changed successfully from %s to %s\n", user->oldEmail, user->newEmail);
}

int main() {
    UserInfo user;
    const char* storedOldEmail = "user@example.com";
    const char* storedPassword = "securepassword123";

    printf("Enter your old email: ");
    scanf("%99s", user.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", user.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", user.confirmPassword);

    changeEmail(&user, storedOldEmail, storedPassword);

    return 0;
}