#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char oldEmail[MAX_EMAIL_LEN];
    char newPassword[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];
} LoginData;

int authenticateUser(const char* email, const char* password) {
    // Simulate authentication (In a real application, this would query a database)
    if (strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Authentication successful
    }
    return 0; // Authentication failed
}

int changeEmail(LoginData data) {
    if (authenticateUser(data.oldEmail, data.confirmPassword)) {
        printf("Authentication successful. Changing email from %s to %s.\n", data.oldEmail, data.newPassword);
        // Simulate changing the email in a database
        return 1; // Email changed successfully
    } else {
        printf("Authentication failed.\n");
        return 0; // Authentication failed
    }
}

int main() {
    LoginData loginData;
    
    printf("Enter your old email: ");
    fgets(loginData.oldEmail, MAX_EMAIL_LEN, stdin);
    loginData.oldEmail[strcspn(loginData.oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your confirm password: ");
    fgets(loginData.confirmPassword, MAX_PASSWORD_LEN, stdin);
    loginData.confirmPassword[strcspn(loginData.confirmPassword, "\n")] = '\0';

    if (!authenticateUser(loginData.oldEmail, loginData.confirmPassword)) {
        printf("Invalid old email or confirmation password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(loginData.newPassword, MAX_EMAIL_LEN, stdin);
    loginData.newPassword[strcspn(loginData.newPassword, "\n")] = '\0';

    if (changeEmail(loginData)) {
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Please check your credentials.\n");
    }

    return 0;
}