#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 5

typedef struct {
    char email[256];
} User;

User usersDatabase[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {"user4@example.com"},
    {"user5@example.com"}
};

int findUserIndex(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(const char *email) {
    int index = findUserIndex(email);
    if (index != -1) {
        for (; index < DATABASE_SIZE - 1; ++index) {
            strcpy(usersDatabase[index].email, usersDatabase[index + 1].email);
        }
        printf("User with email %s has been unsubscribed and removed from the database.\n", email);
    } else {
        printf("Email not found in the database.\n");
    }
}

int main() {
    char inputEmail[256];
    
    printf("Enter email to unsubscribe: ");
    if (fgets(inputEmail, sizeof(inputEmail), stdin) != NULL) {
        size_t len = strlen(inputEmail);
        if (inputEmail[len - 1] == '\n') {
            inputEmail[--len] = '\0'; // Remove newline character
        }
        unsubscribeUser(inputEmail);
    }

    return 0;
}