#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login() {
    char *content_length = getenv("CONTENT_LENGTH");
    int n = content_length ? atoi(content_length) : 0;
    if (n <= 0) return;

    char post_data[n + 1];
    fgets(post_data, n + 1, stdin);

    char username[100] = "", password[100] = "";
    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Admin Page</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login Failed</body></html>");
    }
}