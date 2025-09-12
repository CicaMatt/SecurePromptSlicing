#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 100

typedef struct {
    char email[50];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

void initialize_database() {
    // Simulated pre-existing users for demonstration purposes
    strcpy(database[0].email, "user1@example.com");
    strcpy(database[1].email, "user2@example.com");
    user_count = 2;
}

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        for (int i = index; i < user_count - 1; i++) {
            strcpy(database[i].email, database[i + 1].email);
        }
        user_count--;
        printf("User with email %s has been unsubscribed and removed from the database.\n", email);
    } else {
        printf("The user with email %s is not subscribed to the mailing list.\n", email);
    }
}

void handle_get_request(const char *email) {
    unsubscribe_user(email);
}

int main() {
    initialize_database();

    // Simulate a GET request with an email parameter
    const char *request_email = "user1@example.com";
    
    printf("Processing GET request to unsubscribe endpoint with email: %s\n", request_email);
    handle_get_request(request_email);

    // Test another email not in the database
    const char *another_request_email = "nonexistent@example.com";
    printf("\nProcessing GET request to unsubscribe endpoint with email: %s\n", another_request_email);
    handle_get_request(another_request_email);

    return 0;
}