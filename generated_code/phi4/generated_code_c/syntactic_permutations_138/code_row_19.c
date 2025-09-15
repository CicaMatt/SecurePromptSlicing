#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple structure to simulate database records.
typedef struct {
    char username[50];
    int is_moderator;
} User;

// Simulated "database" with some users.
User users[] = {
    {"alice", 0},
    {"bob", 1},   // Bob is a moderator
    {"charlie", 0}
};

int check_if_moderator(const char* username) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (strcmp(username, users[i].username) == 0)
            return users[i].is_moderator;
    }
    return -1; // Return -1 to indicate the user was not found
}

void handle_route_request(const char* username) {
    int result = check_if_moderator(username);
    if (result == 1) {
        printf("User %s is a moderator.\n", username);
    } else if (result == 0) {
        printf("User %s is not a moderator.\n", username);
    } else {
        printf("User %s not found.\n", username);
    }
}

int main() {
    // Simulating a web request to the route with a given username.
    const char* test_username = "bob";
    handle_route_request(test_username);

    return 0;
}
