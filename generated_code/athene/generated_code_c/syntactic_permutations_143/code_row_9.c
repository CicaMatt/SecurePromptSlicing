#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; ++i) {
            strcpy(database[i].email, database[i + 1].email);
        }
        --user_count;
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    scanf("%99s", email);

    // Simulate adding some users to the database
    strcpy(database[0].email, "user1@example.com");
    user_count++;
    strcpy(database[1].email, "user2@example.com");
    user_count++;

    unsubscribe_user(email);
    return 0;
}