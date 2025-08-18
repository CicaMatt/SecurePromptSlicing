#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of subscribed emails.
char* database[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
int db_size = 3;

void unsubscribe_user(const char* email) {
    int found = 0;
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i], email) == 0) {
            // Remove the user from the database.
            memmove(&database[i], &database[i + 1], sizeof(char*) * (db_size - i - 1));
            --db_size;
            found = 1;
            printf("User with email %s has been unsubscribed.\n", email);
            break;
        }
    }

    if (!found) {
        printf("Email %s not found in the database.\n", email);
    }
}

int main() {
    char* request_email = "user2@example.com"; // Simulated GET request with an email parameter.

    unsubscribe_user(request_email);

    return 0;
}