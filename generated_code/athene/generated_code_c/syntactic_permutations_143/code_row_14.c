#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LEN 50

typedef struct {
    char emails[MAX_EMAILS][EMAIL_LEN];
    int count;
} MailingList;

MailingList mailingList = { .count = 0 };

void init_mailing_list() {
    // Example initialization with some emails
    strcpy(mailingList.emails[mailingList.count++], "user1@example.com");
    strcpy(mailingList.emails[mailingList.count++], "user2@example.com");
}

int find_email(const char *email) {
    for (int i = 0; i < mailingList.count; i++) {
        if (strcmp(mailingList.emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_email(int index) {
    if (index >= 0 && index < mailingList.count) {
        for (int i = index; i < mailingList.count - 1; i++) {
            strcpy(mailingList.emails[i], mailingList.emails[i + 1]);
        }
        mailingList.count--;
    }
}

void handle_unsubscribe(const char *email) {
    int index = find_email(email);
    if (index != -1) {
        remove_email(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    init_mailing_list();
    handle_unsubscribe(argv[1]);

    return 0;
}