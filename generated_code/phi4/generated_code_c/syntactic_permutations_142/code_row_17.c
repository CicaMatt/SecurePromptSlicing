#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Simulated database of emails
char emailDatabase[][MAX_EMAIL_LENGTH] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};
const int databaseSize = sizeof(emailDatabase) / sizeof(emailDatabase[0]);

void unsubscribe(const char *email) {
    for (int i = 0; i < databaseSize; ++i) {
        if (strcmp(emailDatabase[i], email) == 0) {
            // Remove the email from the "database"
            strcpy(emailDatabase[i], "");
            printf("Email %s has been successfully unsubscribed.\n", email);
            return;
        }
    }
    printf("The email address %s is not in the database.\n", email);
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH];

    // Prompt user for their email
    printf("Enter your email to unsubscribe: ");
    fgets(userEmail, MAX_EMAIL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(userEmail);
    if (len > 0 && userEmail[len - 1] == '\n') {
        userEmail[len - 1] = '\0';
    }

    // Call the unsubscribe function with the provided email
    unsubscribe(userEmail);

    return 0;
}