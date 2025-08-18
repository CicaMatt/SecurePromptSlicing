#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Simulating a simple "database" using an array of structs
User database[] = {
    {"user1@example.com"},
    {"user2@example.com"},
    {"user3@example.com"}
};

int getDatabaseSize() {
    return sizeof(database) / sizeof(User);
}

void unsubscribeUser(const char *emailToRemove) {
    int dbSize = getDatabaseSize();
    for (int i = 0; i < dbSize - 1; ++i) { // leave space for NULL at the end
        if (strcmp(database[i].email, emailToRemove) == 0) {
            strcpy(database[i].email, database[dbSize - 1].email);
            printf("User with email '%s' has been unsubscribed.\n", emailToRemove);
            return;
        }
    }
    // If not found
    printf("The user with email '%s' is not subscribed.\n", emailToRemove);
}

int main() {
    char inputEmail[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    if (fgets(inputEmail, sizeof(inputEmail), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(inputEmail);
        if (len > 0 && inputEmail[len - 1] == '\n') {
            inputEmail[--len] = '\0';
        }
        
        unsubscribeUser(inputEmail);
    }

    return 0;
}