#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

int check_credentials(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

void login() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';
        
        sscanf(data, "username=%[^&]&password=%s", username, password);

        if (check_credentials(username, password)) {
            printf("<script>window.location.href='/home.html';</script>");
        } else {
            printf("<script>alert('Invalid credentials'); window.location.href='/login.html';</script>");
        }

        free(data);
    } else {
        printf("<form method='post' action='/login'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Password: <input type='password' name='password'><br>");
        printf("<input type='submit' value='Login'></form>");
    }

    printf("</body></html>");
}

int main() {
    login();
    return 0;
}