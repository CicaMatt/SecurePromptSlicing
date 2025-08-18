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

char* handle_unsubscribe(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            // Remove the user from the database
            for (int j = i; j < user_count - 1; ++j) {
                strcpy(database[j].email, database[j + 1].email);
            }
            --user_count;
            return "User unsubscribed successfully.";
        }
    }
    return "User is not subscribed.";
}

int main() {
    // Simulate adding users to the database
    const char *emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    for (int i = 0; i < sizeof(emails) / sizeof(emails[0]); ++i) {
        strncpy(database[user_count].email, emails[i], MAX_EMAIL_LENGTH);
        ++user_count;
    }

    // Simulate a GET request with an email parameter
    const char *request_email = "user2@example.com";
    char *result = handle_unsubscribe(request_email);

    printf("%s\n", result);
    return 0;
}