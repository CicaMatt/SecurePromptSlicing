#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User *users = NULL;
size_t user_count = 0;

int find_user_index(const char *email) {
    for (size_t i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

int add_user(const char *email) {
    users = realloc(users, sizeof(User) * (user_count + 1));
    if (!users) return -1;

    strncpy(users[user_count].email, email, MAX_EMAIL_LENGTH);
    user_count++;
    return 0;
}

int delete_user(const char *email) {
    int index = find_user_index(email);
    if (index == -1) return -1;

    for (size_t i = index; i < user_count - 1; ++i) {
        users[i] = users[i + 1];
    }
    user_count--;

    users = realloc(users, sizeof(User) * user_count);
    if (users && user_count == 0) {
        free(users);
        users = NULL;
    }

    return 0;
}

void handle_unsubscribe_request(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        delete_user(email);
        printf("User with email %s unsubscribed successfully.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate adding users to the database
    add_user("user1@example.com");
    add_user("user2@example.com");

    char email[MAX_EMAIL_LENGTH];

    printf("Enter email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        size_t len = strlen(email);
        if (email[len - 1] == '\n') {
            email[--len] = '\0'; // Remove newline character
        }
        handle_unsubscribe_request(email);
    }

    free(users);
    return 0;
}