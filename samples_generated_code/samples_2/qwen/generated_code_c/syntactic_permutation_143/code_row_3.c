#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_LENGTH 100
#define DATABASE_SIZE 10

typedef struct {
    char email[EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};
int user_count = 3;

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    for (int i = index; i < user_count - 1; i++) {
        strcpy(database[i].email, database[i + 1].email);
    }
    user_count--;
}

int main() {
    const char *email = "user2@example.com"; // Simulating GET request parameter

    int index = find_user_index(email);

    if (index != -1) {
        delete_user(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("The user is not subscribed.\n");
    }

    return 0;
}