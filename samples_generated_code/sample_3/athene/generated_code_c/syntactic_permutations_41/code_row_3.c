#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User *create_user(const char *username, const char *email, const char *ssn) {
    User *user = (User *)malloc(sizeof(User));
    user->username = strdup(username);
    user->email = strdup(email);
    user->ssn = strdup(ssn);
    return user;
}

void free_user(User *user) {
    free(user->username);
    free(user->email);
    free(user->ssn);
    free(user);
}

void handle_info_route(User *user) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", 4, user->ssn + strlen(user->ssn) - 4);
    printf("</body></html>");
}

int main() {
    // Simulate a user object
    User *user = create_user("johndoe", "john.doe@example.com", "123-45-6789");

    // Handle the /info route
    handle_info_route(user);

    // Clean up
    free_user(user);
    return 0;
}