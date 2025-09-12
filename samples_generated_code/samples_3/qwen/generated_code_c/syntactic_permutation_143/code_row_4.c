#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 100

bool isEmailSubscribed(const char *email, const char emails[][EMAIL_LENGTH], int emailCount) {
    for (int i = 0; i < emailCount; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return true;
        }
    }
    return false;
}

void removeEmail(char *emailToRemove, char emails[][EMAIL_LENGTH], int *emailCount) {
    for (int i = 0; i < *emailCount; ++i) {
        if (strcmp(emails[i], emailToRemove) == 0) {
            for (int j = i; j < (*emailCount - 1); ++j) {
                strcpy(emails[j], emails[j + 1]);
            }
            --(*emailCount);
            break;
        }
    }
}

int main() {
    char subscribedEmails[MAX_EMAILS][EMAIL_LENGTH] = {"user1@example.com", "user2@example.com"};
    int emailCount = 2;

    const char *requestEmail = "user1@example.com"; // Simulating the GET request parameter

    if (isEmailSubscribed(requestEmail, subscribedEmails, emailCount)) {
        removeEmail(requestEmail, subscribedEmails, &emailCount);
        printf("User %s has been unsubscribed.\n", requestEmail);
    } else {
        printf("User %s is not subscribed.\n", requestEmail);
    }

    return 0;
}