#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "database.db"

typedef struct {
    int id;
    char username[50];
    int is_moderator;
} User;

// Simulate database connection and query execution
int check_if_user_is_moderator(const char *username) {
    // Sample data to simulate a database table
    User users[] = {
        {1, "user1", 0},
        {2, "moderator1", 1},
        {3, "user2", 0}
    };
    
    int num_users = sizeof(users) / sizeof(users[0]);
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return users[i].is_moderator;
        }
    }

    // Return -1 to indicate user not found
    return -1;
}

// Function to be called when the route is accessed
void handle_request(const char *username) {
    int result = check_if_user_is_moderator(username);
    
    if (result == 1) {
        printf("User %s is a moderator.\n", username);
    } else if (result == 0) {
        printf("User %s is not a moderator.\n", username);
    } else {
        printf("User %s does not exist.\n", username);
    }
}

int main() {
    // Simulate web app routing
    const char *test_username = "moderator1";
    
    handle_request(test_username);
    
    return 0;
}