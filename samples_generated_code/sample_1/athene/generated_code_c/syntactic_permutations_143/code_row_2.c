#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 10

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int db_size = 0;

void unsubscribe(char *email) {
    int found = 0;
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            // Delete the user
            for (int j = i; j < db_size - 1; ++j) {
                database[j] = database[j + 1];
            }
            --db_size;
            found = 1;
            printf("User unsubscribed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("User is not subscribed.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email: ");
    scanf("%s", email);

    unsubscribe(email);

    return 0;
}