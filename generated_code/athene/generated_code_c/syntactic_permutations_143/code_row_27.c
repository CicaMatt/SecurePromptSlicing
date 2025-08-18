#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 254
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

void add_user_to_database(const char *email) {
    if (user_count < DATABASE_SIZE) {
        strncpy(database[user_count].email, email, MAX_EMAIL_LENGTH - 1);
        database[user_count].email[MAX_EMAIL_LENGTH - 1] = '\0';
        ++user_count;
    }
}

int main() {
    // Example usage
    add_user_to_database("example@example.com");

    const char *email_param = "example@example.com";
    char *result = handle_unsubscribe(email_param);
    printf("%s\n", result);

    return 0;
}