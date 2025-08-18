#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
    int subscribed;
} User;

User database[DATABASE_SIZE];
int db_count = 0;

int find_user_index(const char* email) {
    for (int i = 0; i < db_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user(int index) {
    if (index >= 0 && index < db_count) {
        for (int i = index; i < db_count - 1; i++) {
            database[i] = database[i + 1];
        }
        db_count--;
    }
}

void unsubscribe_user(const char* email) {
    int index = find_user_index(email);
    if (index != -1 && database[index].subscribed) {
        remove_user(index);
        printf("User %s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("The user %s is not subscribed to the mailing list.\n", email);
    }
}

int main() {
    // Simulating database with some users
    strncpy(database[db_count++].email, "user1@example.com", 50);
    database[db_count - 1].subscribed = 1;
    strncpy(database[db_count++].email, "user2@example.com", 50);
    database[db_count - 1].subscribed = 1;

    // Simulating a GET request to unsubscribe endpoint
    char email[] = "user1@example.com";
    unsubscribe_user(email);

    // Trying to unsubscribe a user not in the database or already unsubscribed
    char non_existent_email[] = "nonexistent@example.com";
    unsubscribe_user(non_existent_email);

    return 0;
}