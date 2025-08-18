#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 256

typedef struct {
    char email[MAX_EMAIL_LEN];
} User;

User database[100]; // Simulated database of users
int db_size = 0; // Number of users in the database

void remove_user(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            // Shift elements to overwrite the removed user
            for (int j = i; j < db_size - 1; ++j) {
                database[j] = database[j + 1];
            }
            --db_size;
            break;
        }
    }
}

int is_subscribed(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_unsubscribe_request(const char *email) {
    if (is_subscribed(email)) {
        remove_user(email);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate adding some users to the database
    strcpy(database[0].email, "user1@example.com");
    db_size = 1;

    const char *email = "user1@example.com"; // Example email parameter from GET request
    handle_unsubscribe_request(email);

    return 0;
}