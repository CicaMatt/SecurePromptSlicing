#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int find_user_index(User users[], int size, const char *email) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(User users[], int *size, int index) {
    for (int i = index; i < *size - 1; ++i) {
        users[i] = users[i + 1];
    }
    (*size)--;
}

void unsubscribe(const char *email) {
    const int MAX_USERS = 10;
    User users[MAX_USERS] = {
        {"user1@example.com"},
        {"user2@example.com"},
        {"user3@example.com"}
    };
    int size = 3;

    int index = find_user_index(users, size, email);

    if (index != -1) {
        delete_user(users, &size, index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    const char *email = "user2@example.com";
    
    unsubscribe(email);

    return 0;
}