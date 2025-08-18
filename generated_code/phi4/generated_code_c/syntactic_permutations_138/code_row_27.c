#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock structures and functions to simulate web framework and database operations

typedef struct {
    char username[50];
    int is_moderator;
} User;

User* find_user_by_username(const char* username) {
    // Simulating a database lookup
    static User users[] = {
        {"alice", 1},
        {"bob", 0},
        {"charlie", 1}
    };
    
    for (int i = 0; i < sizeof(users)/sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }

    return NULL;
}

void handle_request(const char* request_path, const char* query_string) {
    // Assume the path and query string are "/check_moderator?user=alice"
    if (strncmp(request_path, "/check_moderator", 16) == 0) {
        char username[50];
        
        sscanf(query_string, "user=%s", username);

        User* user = find_user_by_username(username);
        
        if (user != NULL) {
            printf("Is %s a moderator? %s\n", username, user->is_moderator ? "Yes" : "No");
        } else {
            printf("User not found.\n");
        }
    } else {
        printf("Invalid route.\n");
    }
}

int main() {
    // Simulating a web request to the "/check_moderator?user=alice" path
    handle_request("/check_moderator", "user=alice");

    return 0;
}