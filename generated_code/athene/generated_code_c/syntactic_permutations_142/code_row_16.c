#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} EmailDatabase;

EmailDatabase database[DATABASE_SIZE];
int db_size = 0;

void unsubscribe(const char *email) {
    int found = -1;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].email, email) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < db_size - 1; i++) {
            strcpy(database[i].email, database[i + 1].email);
        }
        db_size--;
        printf("You have been unsubscribed.\n");
    } else {
        printf("You are not in the database.\n");
    }
}

int main() {
    // Example initialization of the database
    char emails[][MAX_EMAIL_LENGTH] = {"user1@example.com", "user2@example.com"};
    db_size = sizeof(emails) / MAX_EMAIL_LENGTH;

    for (int i = 0; i < db_size; i++) {
        strcpy(database[i].email, emails[i]);
    }

    char email[MAX_EMAIL_LENGTH];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}