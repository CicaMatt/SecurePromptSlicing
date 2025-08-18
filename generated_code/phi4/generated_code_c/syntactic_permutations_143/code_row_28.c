#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes.
#define DATABASE_SIZE 3

typedef struct {
    char email[50];
} User;

User usersDatabase[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int isEmailInDatabase(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

void deleteUserFromDatabase(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            // Shift remaining users
            memmove(&usersDatabase[i], &usersDatabase[i + 1], sizeof(User) * (DATABASE_SIZE - i - 1));
            printf("User with email %s has been unsubscribed.\n", email);
            return;
        }
    }
}

void handleUnsubscribeRequest(const char *email) {
    if (isEmailInDatabase(email)) {
        deleteUserFromDatabase(email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    const char *email = "user2@example.com"; // Example GET request parameter.
    handleUnsubscribeRequest(email);

    return 0;
}