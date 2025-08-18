#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[100]; // Assume max 100 users in the database
int user_count = 0; // Number of users currently in the database

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; ++i) {
            database[i] = database[i + 1];
        }
        --user_count;
    }
}

void handle_unsubscribe_request(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        remove_user(index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Simulate a GET request with an email parameter
    const char *email = "example@example.com";
    
    handle_unsubscribe_request(email);

    return 0;
}