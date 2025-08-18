#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} session;

session current_session = { NULL };

void set_header(const char *content_type) {
    printf("Content-type: %s\r\n", content_type);
}

void redirect(const char *url) {
    printf("Location: %s\r\n\r\n", url);
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        current_session.username = strdup(username);
        redirect("/secret");
        return 1;
    }
    return 0;
}

void index() {
    set_header("text/html");
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\r\n");
}

void login_form() {
    set_header("text/html");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("<label>Username: <input type=\"text\" name=\"username\"></label><br>");
    printf("<label>Password: <input type=\"password\" name=\"password\"></label><br>");
    printf("<button type=\"submit\">Login</button>");
    printf("</form></body></html>\r\n");
}

void secret() {
    if (current_session.username == NULL) {
        redirect("/login");
        return;
    }
    set_header("text/html");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("<p>Welcome, %s!</p>", current_session.username);
    printf("</body></html>\r\n");
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    const char *path_info = getenv("PATH_INFO");

    if (strcmp(request_method, "GET") == 0) {
        if (path_info == NULL || strcmp(path_info, "/") == 0) {
            index();
        } else if (strcmp(path_info, "/login") == 0) {
            login_form();
        } else if (strcmp(path_info, "/secret") == 0) {
            secret();
        }
    } else if (strcmp(request_method, "POST") == 0 && strcmp(path_info, "/do_login") == 0) {
        const char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = atoi(content_length_str);
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        char username[100], password[100];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    }

    return 0;
}