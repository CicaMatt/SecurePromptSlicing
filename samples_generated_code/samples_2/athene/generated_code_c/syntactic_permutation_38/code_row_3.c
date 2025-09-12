#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void showLoginPage() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void handleLoginRequest(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome %s!</h1>", username);
        printf("</body></html>");
    } else {
        showLoginPage();
        printf("<p>Invalid username or password</p>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "GET") == 0) {
        showLoginPage();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        char *username = strstr(buffer, "username=");
        char *password = strstr(buffer, "password=");
        if (username && password) {
            username += 9; // length of "username="
            password += 9; // length of "password="
            char username_value[100], password_value[100];
            sscanf(username, "%[^&]", username_value);
            sscanf(password, "%s", password_value);
            handleLoginRequest(username_value, password_value);
        } else {
            showLoginPage();
        }
    }
    return 0;
}