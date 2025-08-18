#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} User;

void free_user(User *user) {
    free(user->username);
    free(user->email);
    free(user->ssn_last_4);
}

User *create_user(const char *username, const char *email, const char *ssn_last_4) {
    User *user = (User *)malloc(sizeof(User));
    user->username = strdup(username);
    user->email = strdup(email);
    user->ssn_last_4 = strdup(ssn_last_4);
    return user;
}

void handle_info_request(User *user) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %s</p>", user->ssn_last_4);
    printf("</body></html>");
}

int main() {
    User *user = create_user("john_doe", "john.doe@example.com", "1234");
    handle_info_request(user);
    free_user(user);
    return 0;
}