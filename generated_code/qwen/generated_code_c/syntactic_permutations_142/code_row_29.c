#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

int findEmail(const char *email, char emails[][EMAIL_LENGTH], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(char *email, char emails[][EMAIL_LENGTH], int *size) {
    int index = findEmail(email, emails, *size);
    if (index != -1) {
        for (int i = index; i < (*size - 1); i++) {
            strcpy(emails[i], emails[i + 1]);
        }
        (*size)--;
        printf("You have been unsubscribed.\n");
    } else {
        printf("Email not found. You are not subscribed.\n");
    }
}

int main() {
    char emails[MAX_EMAILS][EMAIL_LENGTH] = {
        "example1@example.com",
        "example2@example.com",
        "example3@example.com"
    };
    int size = 3;

    char email[EMAIL_LENGTH];
    printf("Enter your email address to unsubscribe: ");
    scanf("%s", email);

    unsubscribe(email, emails, &size);

    return 0;
}