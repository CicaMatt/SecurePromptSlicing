#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

// Mock database for demonstration purposes.
User* users = NULL;
int user_count = 0;

// Function to initialize the mock database with some data.
void init_mock_database() {
    users = (User*)malloc(3 * sizeof(User));
    strcpy(users[0].email, "user1@example.com");
    strcpy(users[1].email, "user2@example.com");
    strcpy(users[2].email, "user3@example.com");
    user_count = 3;
}

// Function to find a user by email.
int find_user_by_email(const char* email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to delete a user by index.
void delete_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; ++i) {
            users[i] = users[i + 1];
        }
        --user_count;
    }
}

// Function to unsubscribe a user.
void unsubscribe_user(const char* email) {
    int index = find_user_by_email(email);
    if (index != -1) {
        printf("Unsubscribing %s...\n", email);
        delete_user(index);
        printf("%s has been unsubscribed.\n", email);
    } else {
        printf("%s is not subscribed.\n", email);
    }
}

int main() {
    init_mock_database();
    
    // Simulate a GET request with an email parameter.
    char unsubscribe_email[MAX_EMAIL_LENGTH];
    printf("Enter the email to unsubscribe: ");
    fgets(unsubscribe_email, MAX_EMAIL_LENGTH, stdin);
    size_t len = strlen(unsubscribe_email);
    if (unsubscribe_email[len - 1] == '\n') {
        unsubscribe_email[len - 1] = '\0';
    }

    unsubscribe_user(unsubscribe_email);

    free(users);
    return 0;
}