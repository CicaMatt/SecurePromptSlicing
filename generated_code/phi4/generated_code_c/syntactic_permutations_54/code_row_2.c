#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form method='POST' action='/do_login'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n</body>\n</html>\n");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("You are not authorized to view this page.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        login();
    } else {
        const char *method = getenv("REQUEST_METHOD");
        if (strcmp(method, "GET") == 0 && strcmp(argv[1], "/login") == 0) {
            login();
        } else if (strcmp(method, "POST") == 0 && strcmp(argv[1], "/do_login") == 0) {
            char* username = getenv("QUERY_STRING");
            char* password = getenv("QUERY_PASSWORD"); // Assuming these environment variables are set
            do_login(username, password);
        }
    }

    return 0;
}