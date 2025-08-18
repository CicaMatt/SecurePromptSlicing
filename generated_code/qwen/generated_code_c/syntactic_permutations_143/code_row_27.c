#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated database of subscribers
typedef struct {
    char *email;
} Subscriber;

#define MAX_SUBSCRIBERS 100
Subscriber subscribers[MAX_SUBSCRIBERS];
int subscriber_count = 0;

// Function to check if an email is in the database
int find_email_index(const char *email) {
    for (int i = 0; i < subscriber_count; i++) {
        if (strcmp(subscribers[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to simulate deleting a subscriber from the database
void delete_subscriber(int index) {
    free(subscribers[index].email);
    for (int i = index; i < subscriber_count - 1; i++) {
        subscribers[i] = subscribers[i + 1];
    }
    subscriber_count--;
}

// Simulated endpoint to handle unsubscribe requests
void unsubscribe_endpoint(const char *email) {
    int index = find_email_index(email);
    if (index != -1) {
        delete_subscriber(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate adding some subscribers to the database
    char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    for (int i = 0; i < 3; i++) {
        subscribers[i].email = strdup(emails[i]);
        subscriber_count++;
    }

    // Simulate a GET request to the unsubscribe endpoint
    const char *request_email = "user2@example.com";
    unsubscribe_endpoint(request_email);

    // Simulate another GET request with an email not in the database
    request_email = "nonexistent@example.com";
    unsubscribe_endpoint(request_email);

    return 0;
}