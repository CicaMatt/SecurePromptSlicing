#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
} User;

typedef struct {
    int (*is_moderator)(User*);
} AppRoute;

typedef struct {
    AppRoute *routes;
} WebApp;

int check_if_moderator(User *user) {
    // Simulate a database query
    if (user && user->username && strcmp(user->username, "moderator") == 0) {
        return 1; // User is a moderator
    }
    return 0; // User is not a moderator
}

void handle_route(AppRoute *route, User *user) {
    int result = route->is_moderator(user);
    printf("Is user a moderator? %s\n", result ? "Yes" : "No");
}

int main() {
    WebApp app;
    AppRoute route;
    route.is_moderator = check_if_moderator;

    User user1 = {"moderator"};
    User user2 = {"user"};

    handle_route(&route, &user1);
    handle_route(&route, &user2);

    return 0;
}