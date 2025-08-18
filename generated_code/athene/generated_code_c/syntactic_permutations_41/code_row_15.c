#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User createUser(const char *username, const char *email, const char *ssn) {
    User user = {strdup(username), strdup(email), strdup(ssn)};
    return user;
}

void freeUser(User *user) {
    free(user->username);
    free(user->email);
    free(user->ssn);
}

void printUserPage(const User *user) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", (int)strlen(user->ssn) - 4, user->ssn + 4);
    printf("</body></html>");
}

int main() {
    // Example user data
    User user = createUser("john_doe", "john.doe@example.com", "123-45-6789");

    printUserPage(&user);

    freeUser(&user);
    return 0;
}