#include <stdio.h>
#include <string.h>

// Mock database structure
typedef struct {
    char email[100];
} EmailDB;

EmailDB database[100];
int db_size = 0;

// Function to simulate a GET request with an email parameter
void handleUnsubscribe(char *email) {
    int found = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].email, email) == 0) {
            // Email found in the database, unsubscribe by removing it
            for (int j = i; j < db_size - 1; j++) {
                strcpy(database[j].email, database[j + 1].email);
            }
            db_size--;
            printf("Email unsubscribed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Email not subscribed.\n");
    }
}

int main() {
    // Simulate adding emails to the database
    strcpy(database[0].email, "example1@example.com");
    db_size++;
    strcpy(database[1].email, "example2@example.com");
    db_size++;

    // Simulate a GET request with an email parameter
    char emailParam[] = "example1@example.com";
    handleUnsubscribe(emailParam);

    return 0;
}