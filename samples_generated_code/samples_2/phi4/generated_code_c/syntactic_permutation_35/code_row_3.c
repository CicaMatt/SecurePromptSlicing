#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_request(char *request) {
    char username[50] = {0};
    char password[50] = {0};

    sscanf(request, "POST /login HTTP/1.1\r\nusername=%49[^&]&password=%49s", username, password);

    if (login(username, password)) {
        printf("HTTP/1.1 302 Found\r\nLocation: /home.html\r\nConnection: close\r\n\r\n");
    } else {
        printf("HTTP/1.1 302 Found\r\nLocation: /login.html\r\nConnection: close\r\n\r\n");
    }
}

int main() {
    char buffer[512];

    // Simulate receiving an HTTP request
    strcpy(buffer, "POST /login HTTP/1.1\r\nusername=user1&password=pass1\r\n");

    handle_request(buffer);

    return 0;
}