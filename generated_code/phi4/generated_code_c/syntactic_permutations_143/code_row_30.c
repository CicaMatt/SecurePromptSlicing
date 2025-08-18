#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Simulated database of users
User usersDatabase[] = {
    {"example1@example.com"},
    {"example2@example.com"},
    {"example3@example.com"}
};
const int dbSize = sizeof(usersDatabase) / sizeof(usersDatabase[0]);

int findUserInDB(const char *email) {
    for (int i = 0; i < dbSize; ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteFromDB(int index) {
    for (int i = index; i < dbSize - 1; ++i) {
        strcpy(usersDatabase[i].email, usersDatabase[i + 1].email);
    }
}

void unsubscribeUser(const char *email) {
    int index = findUserInDB(email);

    if (index != -1) {
        deleteFromDB(index);
        printf("The user %s has been successfully unsubscribed.\n", email);
    } else {
        printf("The user %s is not subscribed.\n", email);
    }
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    if (fgets(userEmail, MAX_EMAIL_LENGTH, stdin)) {
        // Remove newline character from input
        size_t len = strlen(userEmail);
        if (len > 0 && userEmail[len - 1] == '\n') {
            userEmail[--len] = '\0';
        }
        
        unsubscribeUser(userEmail);
    }

    return 0;
}