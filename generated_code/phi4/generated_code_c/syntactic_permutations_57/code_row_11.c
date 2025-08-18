#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 256

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_EMAIL_LEN];
} User;

User currentUser = {"user1", "old@example.com", "password123"};

int verifyPassword(const char* input, const char* correct) {
    return strcmp(input, correct) == 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_EMAIL_LEN];
    int loginSuccess = 0;

    printf("Please log in to change your email.\n");

    // Simulating user input for testing purposes
    printf("Enter old email: ");
    scanf("%255s", oldEmail);
    printf("Enter confirm password: ");
    scanf("%255s", confirmPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && verifyPassword(confirmPassword, currentUser.password)) {
        loginSuccess = 1;
        printf("Login successful.\n");
        
        // Proceed to change email
        printf("Enter new email: ");
        scanf("%255s", newEmail);
        
        if (loginSuccess) {
            strcpy(currentUser.email, newEmail);
            printf("Your email has been updated successfully!\n");
        }
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}