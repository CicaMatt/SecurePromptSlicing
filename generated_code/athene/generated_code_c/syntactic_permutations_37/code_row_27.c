#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "password123"}, {"user1", "pass1"}};
int db_size = sizeof(database) / sizeof(database[0]);

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate reading from form data (for simplicity)
    sscanf(getenv("QUERY_STRING"), "username=%50[^&]&password=%50s", username, password);

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        redirect("/login?error=1");
    }

    return 0;
}