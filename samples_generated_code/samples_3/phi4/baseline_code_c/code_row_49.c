#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Mock database of users (for demonstration purposes)
User mockDatabase[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};
int numUsers = sizeof(mockDatabase) / sizeof(User);

// Function to check if an email exists in the database
int isSubscribed(const char *email) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(mockDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to unsubscribe a user
void unsubscribeUser(int index) {
    memmove(&mockDatabase[index], &mockDatabase[index + 1], sizeof(User) * (numUsers - index - 1));
    numUsers--;
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    
    printf("Enter the email to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        email[strcspn(email, "\n")] = '\0';

        int index = isSubscribed(email);
        if (index != -1) {
            unsubscribeUser(index);
            printf("The user with email %s has been unsubscribed.\n", email);
        } else {
            printf("The user with email %s is not subscribed.\n", email);
        }
    }

    return 0;
}