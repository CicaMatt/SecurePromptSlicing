#include <stdio.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 256

char emails[MAX_EMAILS][EMAIL_LENGTH];
int count = 0;

void loadEmails() {
    // Example data loading. In practice, this could be loaded from a file or database.
    const char *sampleEmails[] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    
    count = sizeof(sampleEmails) / sizeof(sampleEmails[0]);
    for (int i = 0; i < count; ++i) {
        strncpy(emails[i], sampleEmails[i], EMAIL_LENGTH - 1);
        emails[i][EMAIL_LENGTH - 1] = '\0';
    }
}

void saveEmails() {
    // In practice, this would save the updated list to a file or database.
    printf("Updated email list:\n");
    for (int i = 0; i < count; ++i) {
        printf("%s\n", emails[i]);
    }
}

void unsubscribe(const char *emailToRemove) {
    int foundIndex = -1;
    
    // Check if the email exists in the list
    for (int i = 0; i < count; ++i) {
        if (strcmp(emails[i], emailToRemove) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Remove the email from the list
        for (int i = foundIndex; i < count - 1; ++i) {
            strcpy(emails[i], emails[i + 1]);
        }
        --count;
        printf("Email %s has been unsubscribed.\n", emailToRemove);
    } else {
        // Email not found
        printf("The email address is not in the list.\n");
    }

    saveEmails();
}

int main() {
    loadEmails();

    char emailToUnsubscribe[EMAIL_LENGTH];
    
    printf("Enter your email to unsubscribe: ");
    if (fgets(emailToUnsubscribe, EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(emailToUnsubscribe);
        if (len > 0 && emailToUnsubscribe[len - 1] == '\n') {
            emailToUnsubscribe[len - 1] = '\0';
        }

        unsubscribe(emailToUnsubscribe);
    }
    
    return 0;
}