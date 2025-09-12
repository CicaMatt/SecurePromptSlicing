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
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            // Delete the user by shifting all subsequent users one position back
            for (int j = i; j < user_count - 1; j++) {
                database[j] = database[j + 1];
            }
            user_count--;
            return "User unsubscribed successfully.";
        }
    }
    return "User is not subscribed.";
}

int main() {
    // Simulate a GET request with an email parameter
    const char *email_param = "example@example.com";

    char *response = handle_unsubscribe(email_param);
    printf("%s\n", response);

    return 0;
}