#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

int find_user_index(const char* email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; ++i) {
            strcpy(database[i].email, database[i + 1].email);
        }
        --user_count;
    }
}

void handle_unsubscribe_request(const char* email) {
    int index = find_user_index(email);
    if (index != -1) {
        unsubscribe_user(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("The user %s is not subscribed.\n", email);
    }
}

int main(int argc, char* argv[]) {
    // Example database population
    strcpy(database[user_count++].email, "user1@example.com");
    strcpy(database[user_count++].email, "user2@example.com");

    if (argc != 3 || strcmp(argv[1], "GET") != 0) {
        printf("Usage: %s GET email\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_unsubscribe_request(argv[2]);

    return EXIT_SUCCESS;
}