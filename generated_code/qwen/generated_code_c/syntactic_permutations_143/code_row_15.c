#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock database of subscribed emails
#define MAX_EMAILS 100
char subscribedEmails[MAX_EMAILS][50];
int emailCount = 0;

// Function to initialize the mock database with some example data
void initDatabase() {
    strcpy(subscribedEmails[emailCount++], "user1@example.com");
    strcpy(subscribedEmails[emailCount++], "user2@example.com");
    strcpy(subscribedEmails[emailCount++], "user3@example.com");
}

// Function to check if an email is in the database
int isEmailInDatabase(const char *email) {
    for (int i = 0; i < emailCount; i++) {
        if (strcmp(subscribedEmails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to remove an email from the database
void removeFromDatabase(int index) {
    for (int i = index; i < emailCount - 1; i++) {
        strcpy(subscribedEmails[i], subscribedEmails[i + 1]);
    }
    emailCount--;
}

// Simulated function to handle GET request to unsubscribe endpoint
void handleUnsubscribeRequest(const char *email) {
    int index = isEmailInDatabase(email);
    if (index != -1) {
        removeFromDatabase(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    initDatabase();

    // Simulate a GET request to the unsubscribe endpoint
    const char *email = "user2@example.com";
    handleUnsubscribeRequest(email);

    // Another test with an email that is not in the database
    email = "nonexistent@example.com";
    handleUnsubscribeRequest(email);

    return 0;
}