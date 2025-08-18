#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 10

typedef struct {
    char email[50];
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""}
};

int is_email_in_database(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user_from_database(int index) {
    if (index >= 0 && index < DATABASE_SIZE) {
        database[index].email[0] = '\0'; // Mark as deleted
    }
}

int main() {
    char email[50];
    printf("Enter the email to unsubscribe: ");
    scanf("%49s", email);

    int index = is_email_in_database(email);
    if (index != -1) {
        remove_user_from_database(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not found in the database.\n", email);
    }

    return 0;
}