#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_SIZE 256
#define DATABASE_SIZE 10

typedef struct {
    char email[EMAIL_SIZE];
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
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    unsubscribe_user(email);

    return EXIT_SUCCESS;
}