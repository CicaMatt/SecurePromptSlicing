#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_SIZE 10

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int is_email_in_database(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user_from_database(int index) {
    for (int i = index; i < DATABASE_SIZE - 1; ++i) {
        strcpy(database[i].email, database[i + 1].email);
    }
    memset(&database[DATABASE_SIZE - 1], '\0', sizeof(User));
}

void unsubscribe_user(const char *email) {
    int index = is_email_in_database(email);
    if (index != -1) {
        delete_user_from_database(index);
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