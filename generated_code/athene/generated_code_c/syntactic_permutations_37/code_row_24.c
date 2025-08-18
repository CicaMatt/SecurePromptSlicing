#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    const char *username_env = getenv("HTTP_USER_AGENT");
    const char *password_env = getenv("QUERY_STRING");

    if (username_env == NULL || password_env == NULL) {
        redirect("/internal_server_error.html");
        return 1;
    }

    sscanf(username_env, "username=%50[^&]", username);
    sscanf(password_env, "&password=%50s", password);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            redirect("/success.html");
            return 0;
        }
    }

    redirect("/cant_login.html");
    return 0;
}