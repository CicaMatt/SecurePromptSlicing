#include <stdio.h>
#include <string.h>

#define MAX_EMAILS 100

typedef struct {
    char emails[MAX_EMAILS][256];
    int count;
} EmailList;

void unsubscribe(EmailList *list, const char *email) {
    int found = 0;
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->emails[i], email) == 0) {
            found = 1;
            for (int j = i; j < list->count - 1; j++) {
                strcpy(list->emails[j], list->emails[j + 1]);
            }
            list->count--;
            printf("You have been unsubscribed successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Email address not found. You are not subscribed.\n");
    }
}

int main() {
    EmailList list = {0};
    char input[256];

    // Example initialization of the email list
    strcpy(list.emails[0], "user1@example.com");
    strcpy(list.emails[1], "user2@example.com");
    list.count = 2;

    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", input);

    unsubscribe(&list, input);

    return 0;
}