#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LEN 256
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LEN];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void handle_unsubscribe_request(const char *email) {
    int found = 0;
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            found = 1;
            // Shift elements to remove the unsubscribed user
            for (int j = i; j < user_count - 1; ++j) {
                database[j] = database[j + 1];
            }
            user_count--;
            printf("User %s has been successfully unsubscribed.\n", email);
            break;
        }
    }

    if (!found) {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    char email[MAX_EMAIL_LEN];

    // Simulate a GET request with an email parameter
    printf("Enter email to unsubscribe: ");
    scanf("%255s", email);

    handle_unsubscribe_request(email);

    return 0;
}