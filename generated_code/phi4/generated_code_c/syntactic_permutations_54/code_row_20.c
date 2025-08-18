#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
} User;

User users[MAX_USERS] = {
    {"admin", "password123", 1},
    {"user1", "pass1", 0}
};

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/authenticate'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void authenticate(const char *method, const char *postData) {
    if (strcmp(method, "POST") != 0 || postData == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Invalid request method or missing data.\n");
        return;
    }

    char username[50], password[50];
    sscanf(postData, "username=%49[^&]&password=%49s", username, password);

    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (users[i].isAdmin) {
                printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
            } else {
                printf("Content-Type: text/plain\n\n");
                printf("Access Denied.\n");
            }
            return;
        }
    }

    printf("Content-Type: text/plain\n\n");
    printf("Invalid username or password.\n");
}

int main() {
    // Simulate a request
    char *method = "GET";
    char *url = "/login";

    if (strcmp(url, "/login") == 0) {
        login();
    } else if (strcmp(url, "/authenticate") == 0) {
        const char *postData = "username=admin&password=password123"; // Simulated POST data
        authenticate("POST", postData);
    }

    return 0;
}