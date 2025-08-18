#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_SIZE 10

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User users[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int find_user_index(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (int i = index; i < DATABASE_SIZE - 1; ++i) {
            strcpy(users[i].email, users[i + 1].email);
        }
        printf("User with email %s unsubscribed successfully.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    printf("Enter the email to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        unsubscribe_user(email);
    }

    return 0;
}