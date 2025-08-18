#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Simulated database of users
User *users_db = NULL;
int num_users = 0;

void loadDatabase() {
    // Simulating loading from a database with some hardcoded data.
    users_db = (User*)malloc(3 * sizeof(User));
    strcpy(users_db[0].email, "user1@example.com");
    strcpy(users_db[1].email, "user2@example.com");
    strcpy(users_db[2].email, "user3@example.com");
    num_users = 3;
}

int findEmailIndex(const char* email) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users_db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteUser(int index) {
    for (int i = index; i < num_users - 1; ++i) {
        strcpy(users_db[i].email, users_db[i + 1].email);
    }
    --num_users;
}

void handleUnsubscribe(const char* email) {
    int index = findEmailIndex(email);

    if (index != -1) {
        deleteUser(index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main() {
    loadDatabase();

    char email[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        handleUnsubscribe(email);
    } else {
        printf("Error reading input.\n");
    }

    free(users_db);

    return 0;
}