#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char emails[100][MAX_EMAIL_LENGTH];
    int count;
} EmailDatabase;

int emailExists(EmailDatabase *db, const char *email) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeEmail(EmailDatabase *db, const char *email) {
    int index = emailExists(db, email);
    if (index != -1) {
        for (int i = index; i < db->count - 1; ++i) {
            strcpy(db->emails[i], db->emails[i + 1]);
        }
        --db->count;
        printf("Unsubscribed successfully.\n");
    } else {
        printf("Email is not subscribed.\n");
    }
}

void initializeDatabase(EmailDatabase *db, const char *initial_emails[], int size) {
    db->count = size;
    for (int i = 0; i < size; ++i) {
        strcpy(db->emails[i], initial_emails[i]);
    }
}

int main() {
    EmailDatabase db;
    
    const char *initial_emails[] = {"user1@example.com", "user2@example.com", "user3@example.com"};
    initializeDatabase(&db, initial_emails, 3);

    char emailToUnsubscribe[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    scanf("%255s", emailToUnsubscribe);

    unsubscribeEmail(&db, emailToUnsubscribe);
    
    return 0;
}