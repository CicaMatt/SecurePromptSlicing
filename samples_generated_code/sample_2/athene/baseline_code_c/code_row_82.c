#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"admin", "password"},
    {"user1", "pass123"},
    // Add more users if needed
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50], password[50];
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "username=%[^&]&password=%s", username, password);

        if (authenticate(username, password)) {
            printf("<script>window.location.href='/home.html';</script>");
        } else {
            printf("<script>window.location.href='/login.html?error=1';</script>");
        }

        free(data);
    } else {
        printf("Method not allowed");
    }
    
    printf("</body></html>");
}

int main() {
    login();
    return 0;
}