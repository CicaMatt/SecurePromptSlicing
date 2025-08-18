#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

char subscribers[MAX_EMAILS][EMAIL_LENGTH];
int subscriber_count = 0;

bool is_subscribed(const char *email) {
    for (int i = 0; i < subscriber_count; i++) {
        if (strcmp(subscribers[i], email) == 0) {
            return true;
        }
    }
    return false;
}

void unsubscribe_email(const char *email) {
    for (int i = 0; i < subscriber_count; i++) {
        if (strcmp(subscribers[i], email) == 0) {
            // Shift emails to overwrite the unsubscribed one
            for (int j = i; j < subscriber_count - 1; j++) {
                strcpy(subscribers[j], subscribers[j + 1]);
            }
            subscriber_count--;
            printf("User %s has been unsubscribed.\n", email);
            return;
        }
    }
}

void handle_unsubscribe_request(const char *email) {
    if (is_subscribed(email)) {
        unsubscribe_email(email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Example pre-subscribed emails
    strcpy(subscribers[subscriber_count++], "user1@example.com");
    strcpy(subscribers[subscriber_count++], "user2@example.com");

    // Simulate a GET request with an email parameter
    const char *email_param = "user1@example.com";
    handle_unsubscribe_request(email_param);

    return 0;
}