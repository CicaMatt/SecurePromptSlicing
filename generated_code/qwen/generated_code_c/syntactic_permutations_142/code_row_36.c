#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

int findEmail(const char *email, const char emails[MAX_EMAILS][EMAIL_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(const char *email, char emails[MAX_EMAILS][EMAIL_LENGTH], int *count) {
    int index = findEmail(email, emails, *count);
    if (index != -1) {
        for (int i = index; i < (*count - 1); i++) {
            strcpy(emails[i], emails[i + 1]);
        }
        (*count)--;
        printf("You have been unsubscribed successfully.\n");
    } else {
        printf("Email address not found. You are not subscribed.\n");
    }
}

int main() {
    char emails[MAX_EMAILS][EMAIL_LENGTH] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    int count = 3;
    char email[EMAIL_LENGTH];

    printf("Enter your email address to unsubscribe: ");
    scanf("%s", email);

    unsubscribe(email, emails, &count);

    return 0;
}