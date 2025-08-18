#include <stdio.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 256

char emails[MAX_EMAILS][EMAIL_LENGTH];
int count = 0;

void loadEmails() {
    // Example emails to simulate a loaded database
    strcpy(emails[0], "user1@example.com");
    strcpy(emails[1], "user2@example.com");
    strcpy(emails[2], "user3@example.com");
    count = 3;
}

int findEmailIndex(const char* email) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(const char* email) {
    int index = findEmailIndex(email);
    if (index != -1) {
        for (int i = index; i < count - 1; ++i) {
            strcpy(emails[i], emails[i + 1]);
        }
        count--;
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email address not found in the list.\n");
    }
}

int main() {
    loadEmails();
    
    char email[EMAIL_LENGTH];
    printf("Enter your email to unsubscribe: ");
    fgets(email, EMAIL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }

    unsubscribe(email);
    
    return 0;
}