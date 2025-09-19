#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DB_SIZE 10

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User users_db[DB_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int find_user_index(char *email) {
    for (int i = 0; i < DB_SIZE; ++i) {
        if (strcmp(users_db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (; index < DB_SIZE - 1; ++index) {
            strcpy(users_db[index].email, users_db[index + 1].email);
        }
        printf("User %s unsubscribed successfully.\n", email);
    } else {
        printf("The user is not subscribed.\n");
    }
}

int main() {
    char input_email[MAX_EMAIL_LENGTH];

    printf("Enter the email to unsubscribe: ");
    if (fgets(input_email, sizeof(input_email), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(input_email);
        if (len > 0 && input_email[len - 1] == '\n') {
            input_email[--len] = '\0';
        }
        
        unsubscribe_user(input_email);
    }

    return 0;
}