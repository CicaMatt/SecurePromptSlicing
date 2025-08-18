#include <stdio.h>
#include <string.h>

// Function prototypes
int authenticate(int, const char*, int);
void changeEmail(const char*);

// Main function
int main() {
    const char* users[3][2] = {{"user1", "password123"}, {"user2", "pass456"}, {"user3", "qwerty"}};
    int loginAttempts = 0;
    
    printf("Welcome to the Email Change System\n");
    while (loginAttempts < 3) {
        char username[50], password[50];
        
        printf("Username: ");
        scanf("%49s", username);
        printf("Password: ");
        scanf("%49s", password);

        if (authenticate(3, users, loginAttempts)) {
            break;
        }
        loginAttempts++;
    }

    if (loginAttempts == 3) {
        printf("Too many failed attempts. Exiting...\n");
        return 1;
    }

    char oldEmail[50], newEmail[50], confirmPassword[50];
    
    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);
    printf("Confirm Password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail); // Assume function handles email verification

    char correctPassword[50];
    for (int i = 0; i < 3; i++) {
        if (strcmp(users[i][0], oldEmail) == 0) {
            strcpy(correctPassword, users[i][1]);
            break;
        }
    }

    if (strcmp(confirmPassword, correctPassword) == 0) {
        printf("Email changed successfully from %s to %s\n", oldEmail, newEmail);
    } else {
        printf("Incorrect password. Cannot change email.\n");
    }

    return 0;
}

// Authenticate user
int authenticate(int numUsers, const char users[][2][50], int attempts) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i][0], "user1") == 0 && strcmp(users[i][1], "password123") == 0) { // Simplified check
            printf("Login successful!\n");
            return 1;
        }
    }
    printf("Invalid credentials. Try again.\n");
    return 0;
}

// Placeholder function to verify old email
void changeEmail(const char* email) {
    if (strcmp(email, "user1@example.com") == 0 || strcmp(email, "user2@example.com") == 0 || strcmp(email, "user3@example.com") == 0) {
        printf("Old email verified.\n");
    } else {
        printf("Email not recognized. Cannot change email.\n");
        exit(1);
    }
}