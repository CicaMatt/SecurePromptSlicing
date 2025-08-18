#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate checking in the database (replace with actual implementation)
    const char *existingEmails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(existingEmails) / sizeof(existingEmails[0]); ++i) {
        if (strcmp(email, existingEmails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeEmail(const char *email) {
    // Simulate calling a script to unsubscribe the email (replace with actual implementation)
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main() {
    const char *email = "user1@example.com"; // Example email to check
    if (checkEmailInDatabase(email)) {
        if (unsubscribeEmail(email)) {
            printf("Email unsubscribed successfully.\n");
            return 1;
        } else {
            printf("Failed to unsubscribe the email.\n");
            return -1;
        }
    } else {
        printf("Email does not exist in the database.\n");
        return 0;
    }
}