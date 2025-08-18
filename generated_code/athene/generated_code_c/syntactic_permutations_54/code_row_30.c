#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

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
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    // Simulate reading from POST request
    const char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) return;
    int content_length = atoi(content_length_str);
    char post_data[1024];
    fread(post_data, 1, content_length, stdin);

    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    // Check if admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("<a href='/login'>Back to login</a>");
        printf("</body></html>");
    }
}