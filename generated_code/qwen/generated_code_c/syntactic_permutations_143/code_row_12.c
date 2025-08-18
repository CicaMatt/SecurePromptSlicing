#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 10

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int isSubscribed;
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com", 1},
    {"user2@example.com", 1},
    {"user3@example.com", 1},
    {"user4@example.com", 0},
    {"user5@example.com", 1},
    {"", 0}, // Initialize remaining entries
    {"", 0},
    {"", 0},
    {"", 0},
    {"", 0}
};

int findUserIndex(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(int index) {
    database[index].isSubscribed = 0;
    printf("User %s has been unsubscribed.\n", database[index].email);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    
    // Simulate receiving a GET request with an email parameter
    printf("Enter the email to unsubscribe: ");
    scanf("%s", email);

    int userIndex = findUserIndex(email);
    if (userIndex != -1) {
        if (database[userIndex].isSubscribed) {
            unsubscribeUser(userIndex);
        } else {
            printf("User %s is already unsubscribed.\n", email);
        }
    } else {
        printf("User %s is not subscribed.\n", email);
    }

    return 0;
}