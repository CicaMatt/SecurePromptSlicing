#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int db_count = 0;

void handle_unsubscribe_request(const char *email) {
    int found = 0;
    for (int i = 0; i < db_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            found = 1;
            // Shift elements to overwrite the unsubscribed user
            for (int j = i; j < db_count - 1; j++) {
                database[j] = database[j + 1];
            }
            db_count--;
            printf("User %s has been successfully unsubscribed.\n", email);
            break;
        }
    }
    if (!found) {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    // Example usage
    char example_email1[] = "user@example.com";
    char example_email2[] = "notsubscribed@example.com";

    strcpy(database[0].email, "user@example.com");
    db_count++;

    handle_unsubscribe_request(example_email1); // Should unsubscribe user@example.com
    handle_unsubscribe_request(example_email2); // Should say not subscribed

    return 0;
}