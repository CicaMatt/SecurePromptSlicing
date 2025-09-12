#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS] = {
    {"admin", "password123"},
    // Add more predefined users here if necessary.
};

const int user_count = 2; // Adjust based on the number of users in 'users' array.

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Login</title></head>\n");
    printf("<body>\n");
    printf("<form action='/do_login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int do_login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            printf("Location: /admin_page\n\n");
            return 1;
        }
    }
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Login Failed</title></head>\n");
    printf("<body>\n");
    printf("<p>Invalid username or password. <a href='/login'>Try again?</a></p>");
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}

void admin_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Admin Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Admin Page</h1>");
    printf("</body>\n");
    printf("</html>\n");
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /login", 10) == 0) {
        login();
    } else if (strncmp(request, "POST /do_login", 15) == 0) {
        // Extract username and password from the POST request.
        const char *body_start = strstr(request, "\r\n\r\n") + 4;
        char body[USERNAME_LEN + PASSWORD_LEN + 50];
        strncpy(body, body_start, sizeof(body));
        body[sizeof(body) - 1] = '\0';

        char username[USERNAME_LEN], password[PASSWORD_LEN];

        if (sscanf(body, "username=%[^&]&password=%s", username, password) == 2) {
            do_login(username, password);
        }
    } else if (strncmp(request, "GET /admin_page", 15) == 0) {
        admin_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>\n");
    }
}

int main() {
    const char *mock_request = "POST /do_login\r\n"
                               "Content-Length: 42\r\n\r\n"
                               "username=admin&password=password123";

    handle_request(mock_request);

    return 0;
}