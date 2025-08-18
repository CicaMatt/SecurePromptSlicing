#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("\r\n");
}

int check_credentials(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void handle_login() {
    char username[100], password[100];
    
    // Simulate reading from POST data
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<h1>Login Successful</h1>");
    } else {
        redirect("/login.html");
    }
}

int main() {
    handle_login();
    return 0;
}