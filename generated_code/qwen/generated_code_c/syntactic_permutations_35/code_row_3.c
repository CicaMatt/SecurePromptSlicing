#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int check_credentials(const char* username, const char* password) {
    // This function simulates checking credentials against a database.
    // In practice, you would query a real database here.
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0; url=home.html\"></head></html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0; url=login.html\"></head></html>");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate getting data from a form submission
    char* query = getenv("QUERY_STRING");
    if (query != NULL) {
        sscanf(query, "username=%[^&]&password=%s", username, password);
    } else {
        redirect_to_login();
        return 0;
    }

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}