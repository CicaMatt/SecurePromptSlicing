#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char email[50];
} User;

User users[MAX_USERS] = {{"user1@example.com"}, {"user2@example.com"}};
int user_count = 2;

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; ++i) {
            users[i] = users[i + 1];
        }
        --user_count;
        printf("User unsubscribed successfully.\n");
    } else {
        printf("The email is not subscribed.\n");
    }
}

void handle_get_request(const char *email) {
    unsubscribe_user(email);
}

int main() {
    // Simulating a GET request with an email parameter
    const char *email_to_unsubscribe = "user1@example.com";
    
    handle_get_request(email_to_unsubscribe);

    // Attempt to unsubscribe a non-existing user
    const char *non_existent_email = "user3@example.com";
    handle_get_request(non_existent_email);
    
    return 0;
}