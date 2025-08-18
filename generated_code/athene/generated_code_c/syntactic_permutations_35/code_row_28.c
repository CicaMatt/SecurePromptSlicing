#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            printf("Location: home.html\n");
            printf("Content-Type: text/html\n\n");
            return;
        }
    }
    printf("Location: login.html\n");
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate CGI environment variables
    const char *query_string = "username=user1&password=pass1";
    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}