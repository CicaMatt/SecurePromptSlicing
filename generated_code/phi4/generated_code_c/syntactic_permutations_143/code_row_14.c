#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char email[256];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    // Simulate loading from a database or file
    strcpy(users[user_count].email, "user1@example.com");
    user_count++;

    strcpy(users[user_count].email, "user2@example.com");
    user_count++;
}

int find_user(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; i++) {
            strcpy(users[i].email, users[i + 1].email);
        }
        user_count--;
        printf("User with email %s unsubscribed successfully.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    load_users();

    char email_to_unsubscribe[256];
    printf("Enter the email to unsubscribe: ");
    fgets(email_to_unsubscribe, sizeof(email_to_unsubscribe), stdin);
    email_to_unsubscribe[strcspn(email_to_unsubscribe, "\n")] = 0; // Remove newline character

    unsubscribe(email_to_unsubscribe);

    return 0;
}