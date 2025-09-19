#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database check (replace with actual DB logic)
    const char *existing_emails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(existing_emails) / sizeof(existing_emails[0]); ++i) {
        if (strcmp(email, existing_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeEmail(const char *email) {
    char command[256];
    snprintf(command, sizeof(command), "./unsubscribe_script.sh %s", email);
    return system(command) == 0 ? 1 : 0;
}

int main() {
    const char *email = "user1@example.com"; // Example email

    if (!checkEmailInDatabase(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    }

    int unsubscribeResult = unsubscribeEmail(email);
    if (unsubscribeResult == 1) {
        printf("Unsubscribed successfully.\n");
    } else {
        printf("Failed to unsubscribe.\n");
    }

    return unsubscribeResult;
}