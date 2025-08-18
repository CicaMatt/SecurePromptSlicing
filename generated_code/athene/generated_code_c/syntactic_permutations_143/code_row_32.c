#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define NOT_SUBSCRIBED "User is not subscribed.\n"
#define USER_DELETED "User deleted from the database and unsubscribed.\n"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int user_exists(const char *email) {
    // Dummy function to simulate checking if a user exists in the database
    return strcmp(email, "test@example.com") == 0;
}

void delete_user_from_database(const char *email) {
    // Dummy function to simulate deleting a user from the database
    printf(USER_DELETED);
}

void handle_unsubscribe_request(const char *email) {
    if (user_exists(email)) {
        delete_user_from_database(email);
    } else {
        printf(NOT_SUBSCRIBED);
    }
}

int main() {
    const char *email = "test@example.com"; // Example email from GET request
    handle_unsubscribe_request(email);
    return 0;
}