#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User usersDatabase[DATABASE_SIZE];
int databaseCount = 0;

// Mock function to simulate sending GET request with email parameter
void handleGetRequest(const char *email) {
    int found = 0;
    for (int i = 0; i < databaseCount; i++) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            printf("Unsubscribing %s from the mailing list.\n", email);
            
            // Remove user from database
            for (int j = i; j < databaseCount - 1; j++) {
                usersDatabase[j] = usersDatabase[j + 1];
            }
            databaseCount--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("The user %s is not subscribed.\n", email);
    }
}

// Mock function to simulate adding users to the database
void addUserToDatabase(const char *email) {
    if (databaseCount < DATABASE_SIZE) {
        strcpy(usersDatabase[databaseCount].email, email);
        databaseCount++;
    } else {
        printf("Database is full.\n");
    }
}

int main() {
    // Add some users to the database
    addUserToDatabase("user1@example.com");
    addUserToDatabase("user2@example.com");
    
    // Simulate a GET request with an email parameter
    handleGetRequest("user2@example.com");  // Should unsubscribe user2@example.com
    handleGetRequest("user3@example.com");  // Should say the user is not subscribed

    return 0;
}