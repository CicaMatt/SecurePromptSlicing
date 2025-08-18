#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

char session_username[USERNAME_LENGTH] = {0};

int do_login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strncpy(session_username, username, USERNAME_LENGTH);
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void render_login_page() {
    printf("<html><body>\n");
    printf("<h2>Login Page</h2>\n");
    printf("<form action='login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form><br>\n");
    printf("<a href='/logout'>Logout</a> (if logged in)\n");
    printf("</body></html>\n");
}

void render_secret_page() {
    if (session_username[0] != '\0') {
        printf("Secret settings\n");
    } else {
        printf("Access denied. <a href='/login'>Login here</a>\n");
    }
}

void handle_request(const char *request) {
    if (strcmp(request, "GET /") == 0) {
        printf("<html><body>\n");
        printf("<h1>Welcome Page</h1>\n");
        printf("Go to <a href='/login'>Login Page</a> or <a href='/secret'>Secret Page</a>\n");
        printf("</body></html>\n");
    } else if (strcmp(request, "GET /login") == 0) {
        render_login_page();
    } else if (strncmp(request, "POST /login", 11) == 0) {
        const char *username = strstr(request, "username=") + 9;
        const char *password_start = strstr(username, "&password=");
        int username_len = password_start - username;
        const char *password = password_start + 10;

        if (do_login(strndup(username, username_len), strndup(password, PASSWORD_LENGTH))) {
            redirect("/secret");
        } else {
            printf("Invalid credentials. <a href='/login'>Try again</a>\n");
        }
    } else if (strcmp(request, "GET /secret") == 0) {
        render_secret_page();
    } else {
        printf("<html><body>\n");
        printf("<h1>404 Not Found</h1>\n");
        printf("</body></html>\n");
    }
}

int main() {
    char request[] = "POST /login username=user1&password=password1";
    handle_request(request);
    
    return 0;
}