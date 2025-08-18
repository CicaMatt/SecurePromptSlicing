#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char emails[100][MAX_EMAIL_LENGTH];
    int count;
} EmailDatabase;

int connect_to_database(EmailDatabase *db) {
    // Simulating database connection by initializing sample data
    const char *sample_emails[] = {
        "user1@example.com",
        "user2@example.com",
        "user3@example.com"
    };
    db->count = sizeof(sample_emails) / sizeof(sample_emails[0]);
    for (int i = 0; i < db->count; ++i) {
        strcpy(db->emails[i], sample_emails[i]);
    }
    return 1; // Assume connection is successful
}

void unsubscribe(EmailDatabase *db, const char *email_to_remove) {
    int found = 0;
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->emails[i], email_to_remove) == 0) {
            found = 1;
            // Shift emails to the left to remove the unsubscribed one
            for (int j = i; j < db->count - 1; ++j) {
                strcpy(db->emails[j], db->emails[j + 1]);
            }
            --db->count;
            printf("Email %s removed from the database.\n", email_to_remove);
            break;
        }
    }

    if (!found) {
        printf("Email address %s is not in the database.\n", email_to_remove);
    }
}

int main() {
    EmailDatabase db = { .count = 0 };
    char user_email[MAX_EMAIL_LENGTH];

    if (connect_to_database(&db)) {
        printf("Enter your email to unsubscribe: ");
        fgets(user_email, MAX_EMAIL_LENGTH, stdin);

        // Remove newline character from input
        size_t len = strlen(user_email);
        if (len > 0 && user_email[len - 1] == '\n') {
            user_email[len - 1] = '\0';
        }

        unsubscribe(&db, user_email);
    } else {
        printf("Failed to connect to the database.\n");
    }

    return 0;
}