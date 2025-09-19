#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /secret\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body><h1>Logging in...</h1></body></html>\n");
    } else {
        printf("<html><head><title>Login Failed</title></head>");
        printf("<body><h1>Login failed. Please try again.</h1></body></html>\n");
    }
}

void index_page() {
    printf("<html><head><title>Index Page</title></head>");
    printf("<body><a href=\"/login\">Login</a></body></html>\n");
}

void secret_page(const char *username) {
    if (strcmp(username, USERNAME) == 0) {
        printf("<html><head><title>Secret Page</title></head>");
        printf("<body><h1>Secret settings</h1></body></html>\n");
    } else {
        printf("Location: /login\n");
        printf("\n");
        printf("<html><head><title>Access Denied</title></head>");
        printf("<body><h1>You do not have permission to access this page.</h1></body></html>\n");
    }
}

int main() {
    const char *request = getenv("REQUEST_URI");
    if (request == NULL || strcmp(request, "/") == 0) {
        index_page();
    } else if (strcmp(request, "/login") == 0) {
        printf("<html><head><title>Login</title></head>");
        printf("<body><form method=\"post\" action=\"/do_login\">");
        printf("<label for=\"username\">Username:</label>");
        printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
        printf("<label for=\"password\">Password:</label>");
        printf("<input type=\"password\" id=\"password\" name=\"password\"><br>");
        printf("<button type=\"submit\">Login</button>");
        printf("</form></body></html>\n");
    } else if (strcmp(request, "/do_login") == 0) {
        char username[100], password[100];
        sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(request, "/secret") == 0) {
        const char *cookie = getenv("HTTP_COOKIE");
        char username[100] = "";
        if (cookie != NULL && strstr(cookie, "username=")) {
            sscanf(cookie, "username=%[^;]", username);
        }
        secret_page(username);
    } else {
        printf("<html><head><title>404 Not Found</title></head>");
        printf("<body><h1>The requested page was not found.</h1></body></html>\n");
    }
    return 0;
}