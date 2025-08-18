#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char* email) {
    // Simulated database of emails
    const char* emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int numEmails = sizeof(emails) / sizeof(emails[0]);

    for (int i = 0; i < numEmails; ++i) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeScript(const char* email) {
    // Simulated script execution
    printf("Unsubscribing %s...\n", email);
    // Return 0 for success, non-zero for failure
    return 0; // Assume the script always succeeds for this example
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    int exists = checkEmailExists(email);

    if (!exists) {
        return 0;
    }

    int unsubscribeResult = unsubscribeScript(email);
    return (unsubscribeResult == 0) ? 1 : 0;
}