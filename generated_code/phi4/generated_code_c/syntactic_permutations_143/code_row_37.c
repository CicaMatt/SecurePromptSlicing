#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User usersDatabase[DATABASE_SIZE] = {{"user1@example.com"}, {"user2@example.com"}, {"user3@example.com"}};

int isEmailInDatabase(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(usersDatabase[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteUserFromDatabase(int index) {
    for (int i = index; i < DATABASE_SIZE - 1; ++i) {
        usersDatabase[i] = usersDatabase[i + 1];
    }
}

void unsubscribeUser(const char *email) {
    int index = isEmailInDatabase(email);
    if (index != -1) {
        deleteUserFromDatabase(index);
        printf("You have been successfully unsubscribed from the mailing list.\n");
    } else {
        printf("Email not found in the database. Cannot unsubscribe.\n");
    }
}

int main() {
    char email[50];
    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        unsubscribeUser(email);
    }
    return 0;
}