#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("HTTP/1.1 302 Found\n%s", SUCCESS);
            return;
        }
    }
    printf("HTTP/1.1 302 Found\n%s", CANT_LOGIN);
}

int main() {
    char username[50], password[50];
    
    // Simulate reading from a form
    printf("Content-Type: text/html\n\n");
    fgets(username, sizeof(username), stdin);
    fgets(password, sizeof(password), stdin);

    // Remove newline characters if present
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    login(username, password);
    return 0;
}