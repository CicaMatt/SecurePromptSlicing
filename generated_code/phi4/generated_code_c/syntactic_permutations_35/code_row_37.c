#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = 2;

void redirectToLoginPage() {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: login.html\n\n");
}

void redirectToHomePage() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>Welcome to the home page!</body></html>");
}

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (checkCredentials(username, password)) {
        redirectToHomePage();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") == 0) {
        FILE *fp = fopen("php://input", "r");
        if (!fp) {
            printf("HTTP/1.1 500 Internal Server Error\n");
            return 1;
        }

        char buffer[256];
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);

        char username[50] = {0};
        char password[50] = {0};

        sscanf(buffer, "username=%49[^&]&password=%49s", username, password);

        login(username, password);
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
    }

    return 0;
}


**Note:** This code assumes a CGI environment where the server passes HTTP request data via standard input (`php://input`). Adjustments may be needed based on your specific server setup.