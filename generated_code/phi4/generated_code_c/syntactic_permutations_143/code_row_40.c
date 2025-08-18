#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

// Mock database structure
typedef struct {
    char *email;
} UserDatabase;

UserDatabase db[] = {{"user1@example.com"}, {"user2@example.com"}};
int db_size = sizeof(db) / sizeof(UserDatabase);

// Function to find an email in the mock database
int findEmail(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to unsubscribe a user from the mailing list
void unsubscribeUser(const char *email) {
    int index = findEmail(email);
    if (index != -1) {
        free(db[index].email); // Free memory allocated for email
        for (int i = index; i < db_size - 1; ++i) { // Shift remaining elements
            db[i] = db[i + 1];
        }
        db_size--; // Decrease size of the database
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("Email %s not found in the database.\n", email);
    }
}

int main() {
    const char *email_to_unsubscribe = "user1@example.com"; // Example GET request parameter

    unsubscribeUser(email_to_unsubscribe);

    return 0;
}