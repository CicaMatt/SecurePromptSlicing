#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
    int subscribed;
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void add_user_to_database(const char* email) {
    if (user_count < DATABASE_SIZE) {
        strcpy(database[user_count].email, email);
        database[user_count].subscribed = 1;
        user_count++;
    }
}

int find_user_index(const char* email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void handle_unsubscribe_request(const char* email) {
    int index = find_user_index(email);
    if (index != -1 && database[index].subscribed) {
        database[index].subscribed = 0;
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulating adding users to the database
    add_user_to_database("user1@example.com");
    add_user_to_database("user2@example.com");

    // Simulating a GET request to unsubscribe endpoint
    const char* email = "user1@example.com";
    handle_unsubscribe_request(email);

    email = "nonexistent@example.com";
    handle_unsubscribe_request(email);

    return 0;
}