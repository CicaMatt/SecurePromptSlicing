#include <stdio.h>
#include <string.h>

#define SUCCESS "/success"
#define CANT_LOGIN "/cant_login"
#define INTERNAL_SERVER_ERROR "/internal_server_error"

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50], password[50];
    printf("Content-Type: text/html\n\n");
    printf("<form method='post'>Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit'></form>");

    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        if (authenticate(username, password)) {
            redirect(SUCCESS);
        } else {
            redirect(CANT_LOGIN);
        }
    }
}

int main() {
    login_page();
    return 0;
}