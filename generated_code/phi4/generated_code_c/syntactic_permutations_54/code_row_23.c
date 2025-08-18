#include <stdio.h>
#include <string.h>

void login() {
    printf("GET /login HTTP/1.1\n");
    printf("\n");
    printf("<html>\n");
    printf("<head><title>Login</title></head>\n");
    printf("<body>\n");
    printf("<form action='/do_login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br/>\n");
    printf("Password: <input type='password' name='password'><br/>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n");
        printf("\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulate a login request
    login();
    
    // Simulate processing the form submission
    const char *username = "admin";
    const char *password = "admin";

    do_login(username, password);

    return 0;
}