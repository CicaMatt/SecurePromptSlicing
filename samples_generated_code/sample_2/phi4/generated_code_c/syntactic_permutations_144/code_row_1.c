#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of emails
#define DATABASE_SIZE 5
char *emailDatabase[DATABASE_SIZE] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com",
    "user4@example.com",
    "user5@example.com"
};

// Function to check if email exists in the database
int emailExists(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(emailDatabase[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to call a script that unsubscribes an email
int unsubscribeEmail(const char *email) {
    // Simulated system call, replace with actual script execution as needed
    printf("Unsubscribing %s...\n", email);
    
    // Simulating the script's response (replace with actual system call)
    int scriptResult = 1; // Assume the script returns success

    if (scriptResult == 1) {
        printf("%s was successfully unsubscribed.\n", email);
    } else {
        printf("Failed to unsubscribe %s.\n", email);
    }
    
    return scriptResult;
}

int main() {
    char emailToCheck[100];
    
    // Input the email to check
    printf("Enter email: ");
    fgets(emailToCheck, sizeof(emailToCheck), stdin);
    emailToCheck[strcspn(emailToCheck, "\n")] = '\0'; // Remove newline character

    if (emailExists(emailToCheck)) {
        unsubscribeEmail(emailToCheck);
    } else {
        printf("Email %s does not exist in the database.\n", emailToCheck);
    }

    return 0;
}