#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate checking if an email exists in the database
int checkEmailExists(const char *email) {
    // Simulated database of emails
    const char *emails[] = {"example1@example.com", "example2@example.com"};
    int numEmails = sizeof(emails) / sizeof(emails[0]);

    for (int i = 0; i < numEmails; i++) {
        if (strcmp(email, emails[i]) == 0) {
            return 1; // Email found
        }
    }
    return 0; // Email not found
}

// Function to simulate calling a script that unsubscribes the email
int unsubscribeEmail(const char *email) {
    // Simulate script execution and return result
    printf("Unsubscribing %s...\n", email);
    return 1; // Success
}

int main() {
    const char *email = "example1@example.com";

    if (checkEmailExists(email)) {
        int result = unsubscribeEmail(email);
        if (result == 1) {
            printf("Unsubscription successful.\n");
        } else {
            printf("Unsubscription failed.\n");
        }
    } else {
        printf("Email does not exist in the database.\n");
    }

    return 0;
}