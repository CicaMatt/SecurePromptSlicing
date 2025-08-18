#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User database[DATABASE_SIZE] = {0};
int count = 0; // Number of users currently in the database

// Function to check if an email is already subscribed
int is_subscribed(const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to unsubscribe a user
void unsubscribe_user(const char *email) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            found = 1;
            // Move the last element to the current position
            database[i] = database[count - 1];
            // Decrease the count of users
            count--;
            break;
        }
    }

    if (!found) {
        printf("User with email %s is not subscribed.\n", email);
    } else {
        printf("User with email %s has been unsubscribed successfully.\n", email);
    }
}

// Function to simulate handling a GET request
void handle_get_request(const char *email) {
    if (is_subscribed(email)) {
        unsubscribe_user(email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulating adding users to the database
    strcpy(database[0].email, "user1@example.com");
    strcpy(database[1].email, "user2@example.com");
    count = 2;

    char request_email[50];

    printf("Enter the email to unsubscribe: ");
    scanf("%49s", request_email);

    handle_get_request(request_email);

    return 0;
}