#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char email[100];
} User;

User users[] = {{"user1@example.com"}, {"user2@example.com"}};
int user_count = 2;

void handle_unsubscribe(const char *email) {
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            // Remove the user from the database
            for (int j = i; j < user_count - 1; j++) {
                users[j] = users[j + 1];
            }
            user_count--;
            printf("User %s has been unsubscribed.\n", email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User is not subscribed.\n");
    }
}

int main() {
    char email[100];
    printf("Enter email to unsubscribe: ");
    scanf("%99s", email);

    handle_unsubscribe(email);
    return 0;
}