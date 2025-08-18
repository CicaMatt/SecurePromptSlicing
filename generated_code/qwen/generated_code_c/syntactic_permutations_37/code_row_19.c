#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate(const char* username, const char* password) {
    // This is a mock database for demonstration purposes.
    User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
    int num_users = sizeof(users) / sizeof(User);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Content-Type: text/html\r\n\r\n");

    if (fscanf(stdin, "username=%[^&]&password=%[^\n]", username, password) != 2) {
        redirect("internal_server_error.html");
        return EXIT_FAILURE;
    }

    int authenticated = authenticate(username, password);
    if (authenticated) {
        printf("<html><body>Login successful!</body></html>");
    } else {
        redirect("cant_login.html");
    }

    return EXIT_SUCCESS;
}