#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 255

typedef struct {
    char *email;
} User;

User users_db[100]; // Simulated database with a maximum of 100 users.
int db_size = 0;    // Current number of users in the simulated database.

void init_database() {
    // Example data to simulate a pre-populated database
    strcpy(users_db[db_size].email, "user1@example.com");
    db_size++;
    strcpy(users_db[db_size].email, "user2@example.com");
    db_size++;
}

int is_subscribed(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(users_db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(int index) {
    // Shift all users down by one to "delete" the unsubscribed user
    for (int i = index; i < db_size - 1; ++i) {
        strcpy(users_db[i].email, users_db[i + 1].email);
    }
    db_size--;
}

void handle_unsubscribe_request(const char *email) {
    int index = is_subscribed(email);
    if (index != -1) {
        unsubscribe_user(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    init_database();

    char request_email[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    fgets(request_email, MAX_EMAIL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(request_email);
    if (len > 0 && request_email[len - 1] == '\n') {
        request_email[--len] = '\0';
    }

    handle_unsubscribe_request(request_email);

    return 0;
}