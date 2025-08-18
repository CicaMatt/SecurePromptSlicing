#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

typedef struct {
    char emails[MAX_EMAILS][EMAIL_LENGTH];
    int count;
} EmailList;

void loadEmails(EmailList *list) {
    // Example data, normally this would be loaded from a file or database
    const char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    list->count = sizeof(emails) / sizeof(emails[0]);
    for (int i = 0; i < list->count; i++) {
        strncpy(list->emails[i], emails[i], EMAIL_LENGTH);
    }
}

void saveEmails(const EmailList *list) {
    // Normally, this would save to a file or database
    printf("Updated email list:\n");
    for (int i = 0; i < list->count; i++) {
        printf("%s\n", list->emails[i]);
    }
}

int findEmailIndex(const EmailList *list, const char *email) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(EmailList *list, const char *email) {
    int index = findEmailIndex(list, email);
    if (index != -1) {
        for (int i = index; i < list->count - 1; i++) {
            strcpy(list->emails[i], list->emails[i + 1]);
        }
        list->count--;
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email address not found in the subscription list.\n");
    }
}

int main() {
    EmailList emailList;
    loadEmails(&emailList);

    char userEmail[EMAIL_LENGTH];
    printf("Enter your email to unsubscribe: ");
    if (fgets(userEmail, EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(userEmail);
        if (len > 0 && userEmail[len - 1] == '\n') {
            userEmail[len - 1] = '\0';
        }
        unsubscribe(&emailList, userEmail);
    }

    saveEmails(&emailList);

    return 0;
}