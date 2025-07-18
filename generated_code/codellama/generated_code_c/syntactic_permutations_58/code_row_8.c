#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *email;
} User;

User user = {"John Doe", "johndoe@example.com"};

void changeEmail(char *oldEmail, char *newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && authenticate(oldEmail)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Error: could not change email.\n");
    }
}

bool authenticate(char *email) {
    // Check if the user has entered their correct old password.
    char password[32];
    printf("Enter your password: ");
    scanf("%s", password);

    bool validPassword = false;
    while (!validPassword) {
        validPassword = verifyPassword(password);
        if (!validPassword) {
            printf("Invalid password. Try again.\n");
        }
    }

    return true;
}

bool verifyPassword(char *password) {
    // Check the entered password against the stored hashed password.
    char hashedPassword[32];
    strcpy(hashedPassword, user->email);
    strcat(hashedPassword, "123");
    if (strcmp(hashedPassword, password) == 0) {
        return true;
    }
    return false;
}

int main() {
    char oldEmail[64];
    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    char newEmail[64];
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    changeEmail(oldEmail, newEmail);

    return 0;
}