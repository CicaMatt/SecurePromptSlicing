#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int find_user_index(User *users, int count, const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(User **users, int *count, const char *email) {
    int index = find_user_index(*users, *count, email);
    if (index != -1) {
        for (int i = index; i < *count - 1; i++) {
            (*users)[i] = (*users)[i + 1];
        }
        (*count)--;
        printf("User with email %s unsubscribed successfully.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    User users[10] = {
        {"user1@example.com"},
        {"user2@example.com"},
        {"user3@example.com"}
    };
    int count = 3;

    char input_email[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    fgets(input_email, MAX_EMAIL_LENGTH, stdin);
    input_email[strcspn(input_email, "\n")] = '\0'; // Remove newline character

    unsubscribe_user(&users, &count, input_email);

    return 0;
}