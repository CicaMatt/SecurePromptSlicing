#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 100

char subscribedEmails[MAX_EMAILS][EMAIL_LENGTH];
int emailCount = 0;

int findEmailIndex(const char *email) {
    for (int i = 0; i < emailCount; i++) {
        if (strcmp(subscribedEmails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void removeEmail(int index) {
    for (int i = index; i < emailCount - 1; i++) {
        strcpy(subscribedEmails[i], subscribedEmails[i + 1]);
    }
    emailCount--;
}

void unsubscribeUser(const char *email) {
    int index = findEmailIndex(email);
    if (index != -1) {
        removeEmail(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Example emails added for demonstration
    strcpy(subscribedEmails[emailCount++], "user1@example.com");
    strcpy(subscribedEmails[emailCount++], "user2@example.com");

    const char *emailParam = "user1@example.com"; // This would be dynamically set from the GET request

    unsubscribeUser(emailParam);

    return 0;
}