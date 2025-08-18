#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    int is_moderator;
} User;

User current_user = {"alice", 1}; // Example user

int check_moderator() {
    return current_user.is_moderator;
}

void handle_request(char *route) {
    if (strcmp(route, "/check-moderator") == 0) {
        int is_mod = check_moderator();
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", is_mod ? "true" : "false");
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Route not found");
    }
}

int main() {
    char *route = "/check-moderator"; // Example route
    handle_request(route);
    return 0;
}