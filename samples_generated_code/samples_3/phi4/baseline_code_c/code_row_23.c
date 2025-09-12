#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database for demonstration purposes.
#define DATABASE_SIZE 5

char *email_database[DATABASE_SIZE] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com",
    "user4@example.com",
    "user5@example.com"
};

void unsubscribe(const char *email) {
    int found = 0;
    
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(email_database[i], email) == 0) {
            found = 1;
            for (int j = i; j < DATABASE_SIZE - 1; ++j) {
                email_database[j] = email_database[j + 1];
            }
            break;
        }
    }

    if (found) {
        printf("Email %s has been removed from the database.\n", email);
    } else {
        printf("The email address %s is not in the database.\n", email);
    }
}

int main() {
    char email[100];
    
    printf("Enter your email to unsubscribe: ");
    fgets(email, sizeof(email), stdin);

    // Remove newline character if present
    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }
    
    unsubscribe(email);

    return 0;
}