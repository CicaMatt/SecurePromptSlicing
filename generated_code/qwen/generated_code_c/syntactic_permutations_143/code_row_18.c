#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EMAIL_BUFFER_SIZE 100

int check_email_and_unsubscribe(const char* email) {
    // Dummy database of subscribed emails for demonstration
    const char* subscribed_emails[] = {"user@example.com", "test@domain.com"};
    int num_subscribed = sizeof(subscribed_emails) / sizeof(subscribed_emails[0]);

    for (int i = 0; i < num_subscribed; ++i) {
        if (strcmp(email, subscribed_emails[i]) == 0) {
            // Remove from database and unsubscribe logic here
            printf("User with email %s has been unsubscribed.\n", email);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* email = argv[1];
    int result = check_email_and_unsubscribe(email);

    if (!result) {
        printf("The user with email %s is not subscribed.\n", email);
    }

    return 0;
}