#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int find_user(User users[], int count, const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(User users[], int *count, int index) {
    for (int i = index; i < *count - 1; i++) {
        users[i] = users[i + 1];
    }
    (*count)--;
}

int main() {
    // Example database of users
    User users[] = {
        {"user1@example.com"},
        {"user2@example.com"},
        {"user3@example.com"}
    };
    int user_count = sizeof(users) / sizeof(users[0]);

    char email[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);

    // Remove newline character from input if present
    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }

    int user_index = find_user(users, user_count, email);
    if (user_index != -1) {
        delete_user(users, &user_count, user_index);
        printf("User %s has been unsubscribed and removed from the database.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }

    return 0;
}