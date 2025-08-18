#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 100

int checkAndRemoveEmail(const char *email) {
    // Simulated database of email addresses
    const char *database[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    int dbSize = sizeof(database) / sizeof(database[0]);

    for (int i = 0; i < dbSize; i++) {
        if (strcmp(email, database[i]) == 0) {
            // Simulate removing the email from the database
            printf("Email %s has been removed from the database.\n", email);
            return 1;
        }
    }
    return 0;
}

void unsubscribe(const char *email) {
    if (checkAndRemoveEmail(email)) {
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("The email address %s is not in the database.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Failed to read input.\n");
    }

    return 0;
}