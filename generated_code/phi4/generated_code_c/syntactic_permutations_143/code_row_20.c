#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Mock database
User usersDatabase[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};
int totalUsers = sizeof(usersDatabase) / sizeof(usersDatabase[0]);

void unsubscribeUser(const char *email);
int findEmailInDatabase(const char *email);

int main() {
    const char *receivedEmail = "user2@example.com"; // This would be received from the GET request

    if (findEmailInDatabase(receivedEmail)) {
        unsubscribeUser(receivedEmail);
        printf("The user with email %s has been unsubscribed.\n", receivedEmail);
    } else {
        printf("The user with email %s is not subscribed to our mailing list.\n", receivedEmail);
    }

    return 0;
}

int findEmailInDatabase(const char *email) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return 1; // Email found
        }
    }
    return 0; // Email not found
}

void unsubscribeUser(const char *email) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            memmove(&usersDatabase[i], &usersDatabase[i + 1],
                    sizeof(User) * (totalUsers - i - 1));
            totalUsers--;
            break;
        }
    }
}