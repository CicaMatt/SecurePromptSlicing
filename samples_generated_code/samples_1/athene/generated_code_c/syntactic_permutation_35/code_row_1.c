#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int check_login(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void login() {
    char username[100], password[100];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);

    if (check_login(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html?error=1");
    }
}

int main() {
    login();
    return 0;
}