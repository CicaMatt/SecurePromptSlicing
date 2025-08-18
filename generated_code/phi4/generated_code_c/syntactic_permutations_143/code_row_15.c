#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char email[256];
} User;

User users[MAX_USERS];
int user_count = 0;

// Dummy function to simulate database check
int is_email_in_database(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

// Dummy function to simulate database delete
void delete_user_from_database(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            memmove(&users[i], &users[i + 1], sizeof(User) * (user_count - i - 1));
            user_count--;
            printf("User with email %s has been unsubscribed from the mailing list.\n", email);
            return;
        }
    }
}

void unsubscribe_user(const char *email) {
    if (is_email_in_database(email)) {
        delete_user_from_database(email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulating some users in the database
    strcpy(users[0].email, "user1@example.com");
    strcpy(users[1].email, "user2@example.com");
    user_count = 2;

    char request_email[256];
    printf("Enter email to unsubscribe: ");
    scanf("%255s", request_email);

    unsubscribe_user(request_email);

    return 0;
}