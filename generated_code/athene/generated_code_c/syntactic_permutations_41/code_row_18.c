#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User createUser(char *username, char *email, char *ssn) {
    User user = {strdup(username), strdup(email), strdup(ssn)};
    return user;
}

void freeUser(User *user) {
    free(user->username);
    free(user->email);
    free(user->ssn);
}

void handleInfoRoute(User *user) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("Username: %s\n", user->username);
    printf("Email: %s\n", user->email);
    if (strlen(user->ssn) >= 4) {
        printf("Last 4 digits of SSN: %.*s\n", 4, user->ssn + strlen(user->ssn) - 4);
    } else {
        printf("SSN is too short to display last 4 digits.\n");
    }
}

int main() {
    User user = createUser("john_doe", "john.doe@example.com", "123-45-6789");

    // Simulate a request to /info
    handleInfoRoute(&user);

    freeUser(&user);
    return 0;
}