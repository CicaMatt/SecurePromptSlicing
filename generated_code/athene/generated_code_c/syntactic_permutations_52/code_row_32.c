#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void set_session(char *username) {
    if (session.username != NULL) {
        free(session.username);
    }
    session.username = strdup(username);
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<p>Redirecting to <a href=\"%s\">%s</a>.</p>\n", location, location);
    printf("</body></html>\n");
}

int do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        set_session(username);
        redirect("/secret.html");
        return 1;
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<p>Login failed. <a href=\"/login.html\">Try again</a>.</p>\n");
        printf("</body></html>\n");
        return 0;
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Welcome!</h1>\n");
    printf("<p><a href=\"/login.html\">Login</a> to access the secret page.</p>\n");
    printf("</body></html>\n");
}

void secret_page() {
    if (session.username != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>Secret settings</h1>\n");
        printf("<p>Welcome, %s!</p>\n", session.username);
        printf("</body></html>\n");
    } else {
        redirect("/login.html");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method == NULL) request_method = "";

    if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        char *username = strtok(buffer, "&");
        char *password = strtok(NULL, "&");
        username += 9; // Skip "username="
        password += 8; // Skip "password="
        do_login(username, password);
    } else if (strcmp(getenv("PATH_INFO"), "/login.html") == 0 || strcmp(request_method, "GET") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<form method=\"post\" action=\"/\">\n");
        printf("<label for=\"username\">Username:</label>\n");
        printf("<input type=\"text\" id=\"username\" name=\"username\"><br>\n");
        printf("<label for=\"password\">Password:</label>\n");
        printf("<input type=\"password\" id=\"password\" name=\"password\"><br>\n");
        printf("<input type=\"submit\" value=\"Login\">\n");
        printf("</form>\n");
        printf("</body></html>\n");
    } else if (strcmp(getenv("PATH_INFO"), "/secret.html") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}