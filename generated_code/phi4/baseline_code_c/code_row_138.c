#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate web server behavior and database operations
typedef struct {
    char* route;
    void (*handler)(void*);
} Route;

typedef struct {
    int is_moderator;
} User;

int connect_to_database() {
    // Simulate successful connection
    return 1;
}

User query_user_status(const char* username) {
    User user;
    // Mock behavior: assume all users with "mod" in their name are moderators
    if (strstr(username, "mod") != NULL) {
        user.is_moderator = 1;
    } else {
        user.is_moderator = 0;
    }
    return user;
}

void handle_user_check(void* data) {
    const char* username = (const char*)data;

    if (!connect_to_database()) {
        printf("Database connection failed.\n");
        return;
    }

    User user = query_user_status(username);

    if (user.is_moderator) {
        printf("%s is a moderator.\n", username);
    } else {
        printf("%s is not a moderator.\n", username);
    }
}

void start_server() {
    Route routes[] = {{"/check_user", handle_user_check}};
    int num_routes = sizeof(routes) / sizeof(Route);

    // Simulate receiving requests
    const char* test_username = "mod123";
    printf("Handling request for user: %s\n", test_username);
    routes[0].handler(test_username);
}

int main() {
    start_server();
    return 0;
}