#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *password;
} User;

User database[] = {
    {"admin", "1234"},
    {"user", "5678"}
};

#define DATABASE_SIZE (sizeof(database) / sizeof(database[0]))

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
    exit(0);
}

int main() {
    char username[100];
    char password[100];

    // Simulate form input
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);

    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            redirect("/success");
        }
    }

    // If the loop completes without finding a match
    redirect("/cant_login");

    // In case of an unexpected error
    redirect("/internal_server_error");

    return 0;
}