#include <stdio.h>
#include <stdlib.h>
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

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Admin Page</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login Failed</body></html>");
    }
}

int main() {
    char method[10];
    getenv("REQUEST_METHOD") ? strcpy(method, getenv("REQUEST_METHOD")) : strcpy(method, "");
    
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
        char post_data[1024];
        fgets(post_data, content_length + 1, stdin);
        
        char username[100], password[100];
        sscanf(post_data, "username=%[^&]&password=%s", username, password);
        
        do_login(username, password);
    }

    return 0;
}