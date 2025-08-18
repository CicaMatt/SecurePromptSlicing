#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void login() {
    printf("GET /login HTTP/1.1\n");
    printf("\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action='/do_login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_USERNAME_LENGTH];

    // Simulating reading from POST request
    // In a real scenario, these would be populated by parsing the HTTP POST data
    strcpy(username, "admin");  // Example input for testing
    strcpy(password, "password123");  // Example input for testing

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n");
        printf("\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    char method[10];
    printf("Enter HTTP Method (GET/POST): ");
    scanf("%9s", method);

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}