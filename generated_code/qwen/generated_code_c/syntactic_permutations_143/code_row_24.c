#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

char subscribers[MAX_EMAILS][EMAIL_LENGTH];
int subscriber_count = 0;

// Mock function to simulate receiving a GET request
void receive_get_request(const char* email) {
    if (unsubscribe_user(email)) {
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int find_email_index(const char* email) {
    for (int i = 0; i < subscriber_count; ++i) {
        if (strcmp(subscribers[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

int unsubscribe_user(const char* email) {
    int index = find_email_index(email);
    if (index != -1) {
        // Shift elements to overwrite the unsubscribed user
        for (int j = index; j < subscriber_count - 1; ++j) {
            strcpy(subscribers[j], subscribers[j + 1]);
        }
        subscriber_count--;
        return 1;
    }
    return 0;
}

// Mock function to add some initial subscribers
void initialize_subscribers() {
    strcpy(subscribers[subscriber_count++], "user1@example.com");
    strcpy(subscribers[subscriber_count++], "user2@example.com");
    strcpy(subscribers[subscriber_count++], "user3@example.com");
}

int main() {
    initialize_subscribers();
    
    // Simulate receiving a GET request to unsubscribe
    receive_get_request("user2@example.com"); // Should succeed
    receive_get_request("user4@example.com"); // Should fail
    
    return 0;
}