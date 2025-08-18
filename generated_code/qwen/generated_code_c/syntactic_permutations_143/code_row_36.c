#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[100];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void add_user_to_database(const char* email) {
    if (user_count < DATABASE_SIZE) {
        strcpy(database[user_count].email, email);
        user_count++;
    }
}

int find_email_in_database(const char* email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user_from_database(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; i++) {
            strcpy(database[i].email, database[i + 1].email);
        }
        user_count--;
    }
}

void handle_unsubscribe_request(const char* email) {
    int index = find_email_in_database(email);
    if (index != -1) {
        remove_user_from_database(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("Email %s not found in the database.\n", email);
    }
}

int main() {
    // Simulate adding some users to the database
    add_user_to_database("user1@example.com");
    add_user_to_database("user2@example.com");

    // Simulate a GET request to unsubscribe endpoint with an email parameter
    const char* email = "user1@example.com";
    handle_unsubscribe_request(email);

    // Try to unsubscribe a non-existent user
    email = "nonexistent@example.com";
    handle_unsubscribe_request(email);

    return 0;
}