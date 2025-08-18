#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 256

char subscribed_emails[MAX_EMAILS][EMAIL_LENGTH];
int email_count = 0;

void add_email(const char *email) {
    if (email_count < MAX_EMAILS) {
        strcpy(subscribed_emails[email_count++], email);
    }
}

int is_subscribed(const char *email) {
    for (int i = 0; i < email_count; i++) {
        if (strcmp(subscribed_emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_email(int index) {
    if (index >= 0 && index < email_count) {
        for (int i = index; i < email_count - 1; i++) {
            strcpy(subscribed_emails[i], subscribed_emails[i + 1]);
        }
        email_count--;
    }
}

void handle_unsubscribe_request(const char *email) {
    int index = is_subscribed(email);
    if (index != -1) {
        remove_email(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Example: Adding some emails to the list
    add_email("user1@example.com");
    add_email("user2@example.com");
    add_email("user3@example.com");

    // Simulating a GET request with an email parameter
    const char *email_param = "user2@example.com";
    handle_unsubscribe_request(email_param);

    return 0;
}