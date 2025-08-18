#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 5

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User users[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {"user4@example.com"},
    {"user5@example.com"}
};

int findEmailIndex(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(const char *email) {
    int index = findEmailIndex(email);
    if (index != -1) {
        for (int i = index; i < DATABASE_SIZE - 1; ++i) {
            strcpy(users[i].email, users[i + 1].email);
        }
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    printf("Enter the email to unsubscribe: ");
    if (scanf("%100s", email) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    unsubscribeUser(email);

    return 0;
}