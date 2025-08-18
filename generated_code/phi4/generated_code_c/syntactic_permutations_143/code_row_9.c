#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct User {
    char email[MAX_EMAIL_LENGTH];
} User;

User* users = NULL;
int user_count = 0;

int find_user_index(const char* email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    for (int i = index; i < user_count - 1; i++) {
        users[i] = users[i + 1];
    }
    user_count--;
}

void init_users() {
    users = malloc(10 * sizeof(User));
    strcpy(users[0].email, "user1@example.com");
    strcpy(users[1].email, "user2@example.com");
    user_count = 2;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email_to_unsubscribe = argv[1];

    init_users();

    int index = find_user_index(email_to_unsubscribe);
    if (index != -1) {
        delete_user(index);
        printf("User with email %s unsubscribed successfully.\n", email_to_unsubscribe);
    } else {
        printf("User with email %s is not subscribed.\n", email_to_unsubscribe);
    }

    free(users);

    return 0;
}