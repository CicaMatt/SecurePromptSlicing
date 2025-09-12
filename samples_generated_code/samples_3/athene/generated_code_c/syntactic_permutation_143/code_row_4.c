#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LEN 100

typedef struct {
    char emails[MAX_EMAILS][EMAIL_LEN];
    int count;
} MailingList;

MailingList mailingList = { .count = 0 };

void addEmail(const char *email) {
    if (mailingList.count < MAX_EMAILS) {
        strncpy(mailingList.emails[mailingList.count], email, EMAIL_LEN - 1);
        mailingList.emails[mailingList.count][EMAIL_LEN - 1] = '\0';
        mailingList.count++;
    }
}

int findEmailIndex(const char *email) {
    for (int i = 0; i < mailingList.count; i++) {
        if (strcmp(mailingList.emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void removeEmail(int index) {
    if (index >= 0 && index < mailingList.count) {
        for (int i = index; i < mailingList.count - 1; i++) {
            strcpy(mailingList.emails[i], mailingList.emails[i + 1]);
        }
        mailingList.count--;
    }
}

void handleUnsubscribe(const char *email) {
    int index = findEmailIndex(email);
    if (index != -1) {
        removeEmail(index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Example usage
    addEmail("user1@example.com");
    addEmail("user2@example.com");

    const char *email = "user1@example.com";
    handleUnsubscribe(email);

    return 0;
}