#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LEN 50

typedef struct {
    char emails[MAX_EMAILS][EMAIL_LEN];
    int count;
} MailingList;

void unsubscribe(MailingList *list, const char *email) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->emails[i], email) == 0) {
            // Shift elements to remove the unsubscribed user
            for (int j = i; j < list->count - 1; j++) {
                strcpy(list->emails[j], list->emails[j + 1]);
            }
            list->count--;
            printf("User %s has been successfully unsubscribed.\n", email);
            return;
        }
    }
    printf("User %s is not subscribed.\n", email);
}

int main() {
    MailingList mailingList = { .count = 0 };
    
    // Example initialization of the mailing list
    const char *initialEmails[] = {"user1@example.com", "user2@example.com"};
    for (int i = 0; i < sizeof(initialEmails) / sizeof(initialEmails[0]); i++) {
        strcpy(mailingList.emails[i], initialEmails[i]);
        mailingList.count++;
    }

    // Simulate GET request with email parameter
    const char *emailParam = "user1@example.com";
    
    unsubscribe(&mailingList, emailParam);

    return 0;
}