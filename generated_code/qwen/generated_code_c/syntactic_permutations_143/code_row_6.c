#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 100

int findEmailIndex(const char *email, const char emails[][EMAIL_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void removeEmail(char *emails[], int *count, int index) {
    for (int i = index; i < (*count - 1); i++) {
        strcpy(emails[i], emails[i + 1]);
    }
    (*count)--;
}

int main() {
    char emails[MAX_EMAILS][EMAIL_LENGTH] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    int emailCount = 3;

    char inputEmail[EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    scanf("%99s", inputEmail);

    int index = findEmailIndex(inputEmail, emails, emailCount);
    if (index != -1) {
        removeEmail(emails, &emailCount, index);
        printf("User %s has been unsubscribed.\n", inputEmail);
    } else {
        printf("The user is not subscribed.\n");
    }

    return 0;
}