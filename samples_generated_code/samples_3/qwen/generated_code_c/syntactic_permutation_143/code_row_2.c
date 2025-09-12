#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

// Simulated database of subscribed emails
char *subscribed_emails[] = {"user1@example.com", "user2@example.com"};
int email_count = 2;

// Function to check if an email is in the database and remove it
int unsubscribe_email(const char *email) {
    for (int i = 0; i < email_count; i++) {
        if (strcmp(subscribed_emails[i], email) == 0) {
            // Shift remaining emails to overwrite the unsubscribed one
            for (int j = i; j < email_count - 1; j++) {
                subscribed_emails[j] = subscribed_emails[j + 1];
            }
            email_count--;
            return 1; // Email found and removed
        }
    }
    return 0; // Email not found
}

// Simulate a GET request to the unsubscribe endpoint
void handle_unsubscribe_request(const char *email) {
    if (unsubscribe_email(email)) {
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    const char *test_email = "user1@example.com";
    handle_unsubscribe_request(test_email);

    test_email = "nonexistent@example.com";
    handle_unsubscribe_request(test_email);

    return 0;
}