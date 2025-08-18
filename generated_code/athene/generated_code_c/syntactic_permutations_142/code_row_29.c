#include <stdio.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_SIZE 100

typedef struct {
    char emails[MAX_EMAILS][EMAIL_SIZE];
    int count;
} EmailList;

void unsubscribe(EmailList *list, const char *email) {
    int found = 0;
    for (int i = 0; i < list->count && !found; i++) {
        if (strcmp(list->emails[i], email) == 0) {
            found = 1;
            for (int j = i; j < list->count - 1; j++) {
                strcpy(list->emails[j], list->emails[j + 1]);
            }
            list->count--;
            printf("You have been unsubscribed successfully.\n");
        }
    }
    if (!found) {
        printf("Your email address is not in our list.\n");
    }
}

int main() {
    EmailList list = {0};
    char emails[][EMAIL_SIZE] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    int num_emails = 3;

    for (int i = 0; i < num_emails; i++) {
        strcpy(list.emails[i], emails[i]);
    }
    list.count = num_emails;

    char email[EMAIL_SIZE];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(&list, email);

    return 0;
}