#include <stdio.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 256

void unsubscribe(const char *email, const char* emails[], int size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(emails[i], email) == 0) {
            for (; i < size - 1; ++i) {
                strcpy(emails[i], emails[i + 1]);
            }
            printf("User with email %s has been unsubscribed successfully.\n", email);
            return;
        }
    }
    printf("The user with email %s is not subscribed.\n", email);
}

int main() {
    const char* mailingList[MAX_EMAILS] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    
    int size = 3;
    char unsubscribeEmail[EMAIL_LENGTH];

    printf("Enter the email to unsubscribe: ");
    if (scanf("%255s", unsubscribeEmail) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    unsubscribe(unsubscribeEmail, mailingList, size);

    // Optional: Print remaining emails for verification
    printf("\nRemaining subscribed emails:\n");
    for (int i = 0; i < size - 1; ++i) {
        if (mailingList[i][0] != '\0') { // Check if the email slot is not empty
            printf("%s\n", mailingList[i]);
        }
    }

    return 0;
}