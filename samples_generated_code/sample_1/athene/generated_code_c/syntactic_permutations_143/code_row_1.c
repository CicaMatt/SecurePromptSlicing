#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; i++) {
            database[i] = database[i + 1];
        }
        user_count--;
    }
}

void handle_unsubscribe_request(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        delete_user(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate a GET request with an email parameter
    const char *email = "user@example.com";
    handle_unsubscribe_request(email);
    return 0;
}