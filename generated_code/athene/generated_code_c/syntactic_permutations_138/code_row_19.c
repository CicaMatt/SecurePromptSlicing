#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int is_moderator;
} User;

User current_user = {"Alice", 1}; // Example user, 1 means moderator

int check_if_moderator() {
    return current_user.is_moderator;
}

void handle_route() {
    int result = check_if_moderator();
    printf("Is the user a moderator? %s\n", result ? "Yes" : "No");
}

int main() {
    handle_route();
    return 0;
}