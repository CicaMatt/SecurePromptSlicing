#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Simulated database with emails
typedef struct {
    char *email;
} Database;

Database db[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};
const int db_size = sizeof(db) / sizeof(db[0]);

int find_email_index(const char *email) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user_from_db(int index) {
    memmove(&db[index], &db[index + 1], sizeof(Database) * (db_size - index - 1));
    db_size--;
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    
    printf("Enter the email to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove trailing newline character
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }

        int index = find_email_index(email);

        if (index != -1) {
            delete_user_from_db(index);
            printf("User with email %s unsubscribed successfully.\n", email);
        } else {
            printf("Email not found in the database. User is not subscribed.\n");
        }
    }

    return 0;
}