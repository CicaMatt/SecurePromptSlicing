#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "1234"}, {"user", "pass"}};
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

    if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), MAX_USERNAME_LENGTH - 1, stdin);
            fread(password, sizeof(char), MAX_PASSWORD_LENGTH - 1, stdin);

            username[content_length] = '\0';
            password[content_length] = '\0';

            char *username_start = strchr(username, '=');
            char *password_start = strchr(password, '=');

            if (username_start && password_start) {
                *(++username_start) = '\0';
                *(++password_start) = '\0';

                if (authenticate(username_start, password_start)) {
                    redirect("success");
                } else {
                    redirect("cant_login");
                }
            } else {
                redirect("internal_server_error");
            }
        } else {
            redirect("internal_server_error");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<form method='post'>"
               "Username: <input type='text' name='username'><br>"
               "Password: <input type='password' name='password'><br>"
               "<input type='submit' value='Login'>"
               "</form>");
    }
    return 0;
}