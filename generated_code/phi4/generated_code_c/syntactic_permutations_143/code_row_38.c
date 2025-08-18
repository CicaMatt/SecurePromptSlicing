#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char emails[100][MAX_EMAIL_LENGTH];
    int count;
} EmailDatabase;

EmailDatabase db = { .count = 0 };

int email_exists(const char *email) {
    for (int i = 0; i < db.count; ++i) {
        if (strcmp(db.emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void delete_email(const char *email) {
    int found = -1;
    for (int i = 0; i < db.count; ++i) {
        if (strcmp(db.emails[i], email) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < db.count - 1; ++i) {
            strcpy(db.emails[i], db.emails[i + 1]);
        }
        db.count--;
        printf("Email unsubscribed successfully.\n");
    } else {
        printf("Email not found in the database.\n");
    }
}

void add_email(const char *email) {
    if (db.count < 100 && !email_exists(email)) {
        strcpy(db.emails[db.count], email);
        db.count++;
    }
}

int main() {
    // Sample emails for testing
    add_email("test1@example.com");
    add_email("test2@example.com");

    char email_to_unsubscribe[MAX_EMAIL_LENGTH];
    
    printf("Enter the email to unsubscribe: ");
    scanf("%255s", email_to_unsubscribe);

    if (email_exists(email_to_unsubscribe)) {
        delete_email(email_to_unsubscribe);
    } else {
        printf("Email not subscribed.\n");
    }

    return 0;
}