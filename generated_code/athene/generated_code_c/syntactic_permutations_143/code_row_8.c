#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void unsubscribe(char *email) {
    int found = 0;
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            found = 1;
            // Shift remaining users to fill the gap
            for (int j = i; j < user_count - 1; ++j) {
                strcpy(database[j].email, database[j + 1].email);
            }
            --user_count;
            printf("User unsubscribed: %s\n", email);
            break;
        }
    }

    if (!found) {
        printf("User not subscribed: %s\n", email);
    }
}

int main() {
    char request_email[MAX_EMAIL_LENGTH];

    // Simulate a GET request with an email parameter
    printf("Enter email to unsubscribe: ");
    scanf("%255s", request_email);

    unsubscribe(request_email);

    return 0;
}