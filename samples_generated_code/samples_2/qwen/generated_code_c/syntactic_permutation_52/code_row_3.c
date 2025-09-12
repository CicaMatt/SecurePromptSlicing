#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session current_session = {""};

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(current_session.username, username, MAX_USERNAME);
        printf("Location: /secret\n\n");
    } else {
        printf("<html><body>Login Failed. <a href=\"/login\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("<html><body><h1>Welcome to the Index Page</h1><a href=\"/login\">Login here</a></body></html>");
}

void login_page() {
    printf("<html><body>"
           "<form action=\"/do_login\" method=\"post\">"
           "Username: <input type=\"text\" name=\"username\"><br>"
           "Password: <input type=\"password\" name=\"password\"><br>"
           "<input type=\"submit\" value=\"Submit\">"
           "</form></body></html>");
}

void secret_page() {
    if (strlen(current_session.username) > 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login\n\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    char *path_info = getenv("PATH_INFO");

    if (method == NULL || path_info == NULL) {
        index_page();
    } else if (strcmp(path_info, "/") == 0) {
        index_page();
    } else if (strcmp(path_info, "/login") == 0) {
        login_page();
    } else if (strcmp(path_info, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME] = "";
        char password[MAX_PASSWORD] = "";

        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fgets(username, MAX_USERNAME, stdin);
            fgets(password, MAX_PASSWORD, stdin);

            // Remove newline characters
            username[strcspn(username, "\r\n")] = '\0';
            password[strcspn(password, "\r\n")] = '\0';

            char *username_prefix = "username=";
            char *password_prefix = "&password=";

            if (strncmp(username, username_prefix, strlen(username_prefix)) == 0) {
                strcpy(username, username + strlen(username_prefix));
            }
            if (strncmp(password, password_prefix, strlen(password_prefix)) == 0) {
                strcpy(password, password + strlen(password_prefix));
            }

            do_login(username, password);
        } else {
            login_page();
        }
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page();
    } else {
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}