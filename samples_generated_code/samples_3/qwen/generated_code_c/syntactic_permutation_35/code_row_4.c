#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy authentication function for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("</body></html>");
}

void redirect_to_login(const char *message) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login Failed: %s</h2>", message);
    printf("<form action=\"login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    fgets(username, MAX_USERNAME_LENGTH, stdin);
    fgets(password, MAX_PASSWORD_LENGTH, stdin);

    // Remove newline characters
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login("Invalid username or password");
    }

    return 0;
}