#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User createUser(char *username, char *email, char *ssn) {
    User user = { strdup(username), strdup(email), strdup(ssn) };
    return user;
}

char* info(User *user) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", user->username, user->email, user->ssn);
    return response;
}

void handle_request(char *method, User *user) {
    if (strcmp(method, "GET") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", info(user));
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
    }
}

int main() {
    User user = createUser("john_doe", "john.doe@example.com", "123-45-6789");

    // Simulate a GET request to /info
    handle_request("GET", &user);

    free(user.username);
    free(user.email);
    free(user.ssn);

    return 0;
}