#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void handle_unsubscribe(const char *email) {
    int found = -1;
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Remove the user from the database
        for (int i = found; i < user_count - 1; ++i) {
            strcpy(database[i].email, database[i + 1].email);
        }
        --user_count;
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    // Simulate a GET request with an email parameter
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    scanf("%255s", email);

    handle_unsubscribe(email);
    return 0;
}