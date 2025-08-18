#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 100

char emails[MAX_EMAILS][EMAIL_LENGTH] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

int isEmailSubscribed(const char *email) {
    for (int i = 0; i < MAX_EMAILS; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void unsubscribeUser(char *email) {
    for (int i = 0; i < MAX_EMAILS; ++i) {
        if (strcmp(emails[i], email) == 0) {
            strcpy(emails[i], "");
            printf("User with email %s has been unsubscribed.\n", email);
            return;
        }
    }
}

void handleGetRequest(const char *email) {
    if (isEmailSubscribed(email)) {
        unsubscribeUser((char *)email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    char email[EMAIL_LENGTH];
    
    printf("Enter the email to unsubscribe: ");
    scanf("%99s", email);

    handleGetRequest(email);

    return 0;
}