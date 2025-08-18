#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char email[100];
} User;

User users[MAX_USERS];
int user_count = 0;

int find_user(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; i++) {
            users[i] = users[i + 1];
        }
        user_count--;
        printf("User unsubscribed: %s\n", email);
    } else {
        printf("User not subscribed: %s\n", email);
    }
}

int main() {
    // Example initialization of users
    strcpy(users[0].email, "user1@example.com");
    user_count = 1;

    char *email = "user1@example.com"; // This would be the parameter from the GET request

    unsubscribe_user(email);

    return 0;
}