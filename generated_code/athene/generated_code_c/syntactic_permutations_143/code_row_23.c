#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *email;
} User;

User *users[] = {NULL}; // Simulate database with an array of pointers to users
int user_count = 0; // Number of users in the "database"

// Function to find a user by email
User* find_user(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i]->email, email) == 0) {
            return users[i];
        }
    }
    return NULL;
}

// Function to delete a user by email
void delete_user(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i]->email, email) == 0) {
            free(users[i]->email);
            free(users[i]);
            for (; i < user_count - 1; i++) {
                users[i] = users[i + 1];
            }
            users[user_count - 1] = NULL;
            user_count--;
            break;
        }
    }
}

// Simulate a GET request handler
void handle_unsubscribe(const char *email) {
    User *user = find_user(email);
    if (user != NULL) {
        delete_user(email);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Simulate adding users to the database
    char *emails[] = {"alice@example.com", "bob@example.com"};
    for (int i = 0; i < sizeof(emails) / sizeof(char *); i++) {
        User *user = malloc(sizeof(User));
        user->email = strdup(emails[i]);
        users[user_count++] = user;
    }

    // Simulate a GET request to unsubscribe endpoint
    const char *email_to_unsubscribe = "alice@example.com";
    handle_unsubscribe(email_to_unsubscribe);

    return 0;
}