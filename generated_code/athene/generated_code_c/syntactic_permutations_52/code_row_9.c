#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

void set_session(const char *username) {
    printf("Set-Cookie: username=%s; Path=/\n", username);
}

void show_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void handle_login() {
    char username[100], password[100];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(username);
        redirect("/secret");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed</body></html>");
    }
}

void show_index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<a href='/login'>Login</a>");
    printf("</body></html>");
}

void show_secret_page() {
    char *username = getenv("HTTP_COOKIE");
    if (username && strstr(username, "username=") != NULL) {
        username = strstr(username, "username=") + 9;
        if (strstr(username, ";") != NULL) {
            *strstr(username, ";") = '\0';
        }
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome %s</h1>", username);
        printf("<p>Secret settings</p>");
        printf("</body></html>");
    } else {
        redirect("/login");
    }
}

int main() {
    const char *request_uri = getenv("REQUEST_URI");

    if (strcmp(request_uri, "/") == 0) {
        show_index();
    } else if (strcmp(request_uri, "/login") == 0 && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        handle_login();
    } else if (strcmp(request_uri, "/login") == 0) {
        show_login_form();
    } else if (strcmp(request_uri, "/secret") == 0) {
        show_secret_page();
    }

    return 0;
}