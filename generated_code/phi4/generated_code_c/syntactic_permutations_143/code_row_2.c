#include <stdio.h>
#include <string.h>

// Simulating a simple database with an array of emails.
#define MAX_USERS 100
char database[MAX_USERS][256];
int db_size = 0;

// Function to initialize the database with some dummy data
void init_database() {
    strcpy(database[db_size++], "user1@example.com");
    strcpy(database[db_size++], "user2@example.com");
    strcpy(database[db_size++], "user3@example.com");
}

// Function to check if an email is in the database and unsubscribe it
void unsubscribe(char *email) {
    int found = 0;
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i], email) == 0) {
            found = 1;
            // Shift all elements to remove the unsubscribed user
            for (int j = i; j < db_size - 1; ++j) {
                strcpy(database[j], database[j + 1]);
            }
            --db_size;
            printf("User with email %s has been unsubscribed.\n", email);
            break;
        }
    }

    if (!found) {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    init_database();
    
    char input_email[256];
    printf("Enter the email to unsubscribe: ");
    fgets(input_email, sizeof(input_email), stdin);

    // Remove newline character from the input
    size_t len = strlen(input_email);
    if (len > 0 && input_email[len - 1] == '\n') {
        input_email[--len] = '\0';
    }

    unsubscribe(input_email);
    
    return 0;
}