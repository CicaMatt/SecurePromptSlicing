#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define PASSWORD_LENGTH 20

struct User {
    char username[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

void clearScreen() {
    // Portable way to clear the console screen
    printf("\033[H\033[J");
}

int authenticate(struct User *user) {
    char inputPassword[PASSWORD_LENGTH];

    printf("Enter your password: ");
    fgets(inputPassword, PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    return strcmp(user->password, inputPassword) == 0;
}

int updateEmail(struct User *user) {
    char oldEmail[MAX_NAME_LENGTH];
    char newEmail[MAX_NAME_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_NAME_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    if (strcmp(user->email, oldEmail) != 0) {
        printf("Incorrect email!\n");
        return 0;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_NAME_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    if (strcmp(user->email, newEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 0;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Incorrect password!\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email updated successfully.\n");

    return 1;
}

int main() {
    struct User user = {"john_doe", "john@example.com", "securePassword123"};

    while (1) {
        clearScreen();

        printf("Welcome to the login page!\n\n");
        printf("Enter your username: ");
        fgets(user.username, MAX_NAME_LENGTH, stdin);
        user.username[strcspn(user.username, "\n")] = '\0'; // Remove newline character

        if (!authenticate(&user)) {
            printf("\nAuthentication failed! Try again.\n");
            continue;
        }

        int result = updateEmail(&user);

        if (result) {
            break; // Exit loop on successful email update
        }
    }

    return 0;
}