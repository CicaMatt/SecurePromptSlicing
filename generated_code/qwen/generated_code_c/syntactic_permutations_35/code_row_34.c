#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    // This function should load users from a database or file
    // For demonstration, we'll just add some hardcoded users
    strcpy(users[0].username, "user1");
    strcpy(users[0].password, "pass1");
    user_count = 1;
}

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char* username, const char* password) {
    if (authenticate(username, password)) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: home.html\n\n");
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: login.html\n\n");
    }
}

int main() {
    load_users();

    // Simulate receiving a POST request with username and password
    const char* method = getenv("REQUEST_METHOD");
    if (method != NULL && strcmp(method, "POST") == 0) {
        char buffer[1024];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(buffer, content_length + 1, stdin);

        // For simplicity, we assume the input format is "username=user&password=pass"
        char username[USERNAME_LEN], password[PASSWORD_LEN];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);
        handle_login(username, password);
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
        printf("Content-Type: text/plain\n\n");
        printf("Only POST method is allowed.\n");
    }

    return 0;
}