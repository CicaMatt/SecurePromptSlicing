#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
#define MAX_USERS 100
char database[MAX_USERS][50] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};
int user_count = 3;

// Function to simulate sending a response back to the client
void send_response(const char* message) {
    printf("Response: %s\n", message);
}

// Function to check if an email exists in the database and remove it
int unsubscribe_user(const char* email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i], email) == 0) {
            // Remove the user from the database by shifting subsequent entries up
            for (int j = i; j < user_count - 1; j++) {
                strcpy(database[j], database[j + 1]);
            }
            user_count--;
            return 1; // User found and unsubscribed
        }
    }
    return 0; // User not found
}

// Simulated GET request handler
void handle_get_request(const char* email) {
    if (unsubscribe_user(email)) {
        send_response("You have been successfully unsubscribed.");
    } else {
        send_response("User is not subscribed.");
    }
}

int main() {
    // Example usage: simulating a GET request with an email parameter
    const char* email = "user2@example.com";
    handle_get_request(email);

    return 0;
}