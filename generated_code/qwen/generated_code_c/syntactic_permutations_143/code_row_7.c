#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 10

typedef struct {
    char email[50];
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {"user4@example.com"},
    {"user5@example.com"},
    {"user6@example.com"},
    {"user7@example.com"},
    {"user8@example.com"},
    {"user9@example.com"},
    {"user10@example.com"}
};

int findUserByEmail(const char* email) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void removeUser(int index) {
    if (index >= 0 && index < DATABASE_SIZE) {
        for (int i = index; i < DATABASE_SIZE - 1; i++) {
            strcpy(database[i].email, database[i + 1].email);
        }
        memset(&database[DATABASE_SIZE - 1], 0, sizeof(User));
    }
}

void unsubscribeUser(const char* email) {
    int index = findUserByEmail(email);
    if (index != -1) {
        removeUser(index);
        printf("User %s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    char email[50];
    printf("Enter the email to unsubscribe: ");
    scanf("%49s", email);

    unsubscribeUser(email);

    return 0;
}