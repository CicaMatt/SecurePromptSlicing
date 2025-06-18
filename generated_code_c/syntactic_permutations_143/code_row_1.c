#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50

struct Subscriber {
    char email[MAX_EMAIL_LENGTH];
};

struct MailingList {
    struct Subscriber subscribers[100];
    int subscribers_count;
};

bool isSubscribed(char* email, struct MailingList mailingList) {
    for (int i = 0; i < mailingList.subscribers_count; i++) {
        if (strcmp(email, mailingList.subscribers[i].email) == 0) {
            return true;
        }
    }
    return false;
}

void unsubscribe(char* email, struct MailingList* mailingList) {
    for (int i = 0; i < mailingList->subscribers_count; i++) {
        if (strcmp(email, mailingList->subscribers[i].email) == 0) {
            for (int j = i + 1; j < mailingList->subscribers_count; j++) {
                mailingList->subscribers[j - 1] = mailingList->subscribers[j];
            }
            mailingList->subscribers_count--;
            return;
        }
    }
}

int main() {
    struct MailingList mailingList = {{ .email = "user@example.com" }, 1};

    char* email = "user@example.com";

    if (isSubscribed(email, mailingList)) {
        unsubscribe(email, &mailingList);
        printf("Unsubscribed.");
    } else {
        printf("You are not subscribed.");
    }
}