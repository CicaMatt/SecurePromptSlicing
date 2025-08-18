#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form method='post' action='/do_login'>");
    printf("<input type='text' name='username' placeholder='Username'/>");
    printf("<input type='password' name='password' placeholder='Password'/>");
    printf("<button type='submit'>Login</button>");
    printf("</form></body></html>");
}

void do_login() {
    char username[100];
    char password[100];
    // Simulate reading form data (POST request)
    sscanf(getenv("QUERY_STRING"), "username=%s&password=%s", username, password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /user_page\n\n");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Index Page</h1>");
    printf("<a href='/login'>Login</a>");
    printf("</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Page</h1>");
    printf("<p>Welcome, User!</p>");
    printf("</body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Admin Page</h1>");
    printf("<p>Welcome, Admin!</p>");
    printf("</body></html>");
}