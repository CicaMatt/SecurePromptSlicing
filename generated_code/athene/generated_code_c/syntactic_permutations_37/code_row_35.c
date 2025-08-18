#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {{"admin", "1234"}, {"user", "pass"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("Location: /success\n");
            return;
        }
    }
    printf("Location: /cant_login\n");
}

int main() {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), MAX_USERNAME - 1, stdin);
            fread(password, sizeof(char), MAX_PASSWORD - 1, stdin);
            username[MAX_USERNAME - 1] = '\0';
            password[MAX_PASSWORD - 1] = '\0';

            char *token = strtok(username, "&");
            if (token != NULL) {
                sscanf(token, "username=%s", username);
                token = strtok(NULL, "&");
                if (token != NULL) {
                    sscanf(token, "password=%s", password);
                }
            }

            printf("Content-Type: text/html\n\n");
            login(username, password);
        } else {
            printf("Location: /error\n");
        }
    } else {
        printf("Location: /error\n");
    }
    return 0;
}