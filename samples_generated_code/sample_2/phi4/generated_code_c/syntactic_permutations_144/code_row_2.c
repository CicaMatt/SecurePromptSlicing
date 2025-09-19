#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
char *emailDatabase[] = {"user@example.com", "test@domain.com"};
int emailCount = sizeof(emailDatabase) / sizeof(emailDatabase[0]);

// Function to simulate checking if an email exists in the database
int checkEmailExists(const char *email) {
    for (int i = 0; i < emailCount; ++i) {
        if (strcmp(email, emailDatabase[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Mock function to simulate unsubscribing an email
int unsubscribeEmail(const char *email) {
    // Simulate a script call that could succeed or fail
    printf("Unsubscribing %s...\n", email);
    // For demonstration, let's assume it always succeeds (returns 1)
    return 1;
}

// Main function to check and unsubscribe an email
int main() {
    char *email = "test@domain.com";  // Example email

    if (!checkEmailExists(email)) {
        printf("Email %s does not exist in the database.\n", email);
        return 0;
    }

    int result = unsubscribeEmail(email);

    if (result == 1) {
        printf("Unsubscribed %s successfully.\n", email);
        return 1;
    } else {
        printf("Failed to unsubscribe %s.\n", email);
        return 0;
    }
}