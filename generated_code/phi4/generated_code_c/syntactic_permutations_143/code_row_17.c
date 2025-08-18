#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User users[DATABASE_SIZE] = {{"example1@example.com"}, {"example2@example.com"}};
int user_count = 2;

bool find_user_index(const char *email, int *index) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            *index = i;
            return true;
        }
    }
    return false;
}

void unsubscribe_user(const char *email) {
    int index;
    if (find_user_index(email, &index)) {
        // Remove the user from the database
        for (int i = index; i < user_count - 1; ++i) {
            users[i] = users[i + 1];
        }
        --user_count;

        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

void handle_get_request(const char *email) {
    unsubscribe_user(email);
}

int main() {
    const char *test_email = "example1@example.com";
    const char *non_existent_email = "not_in_database@example.com";

    printf("Unsubscribing %s...\n", test_email);
    handle_get_request(test_email);

    printf("\nAttempting to unsubscribe a non-existent email: %s\n", non_existent_email);
    handle_get_request(non_existent_email);

    return 0;
}