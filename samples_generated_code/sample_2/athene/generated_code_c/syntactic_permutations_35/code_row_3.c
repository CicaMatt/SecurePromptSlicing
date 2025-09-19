#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int authenticate(const char *username, const char *password) {
    return (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0);
}

void login() {
    char username[100], password[100];
    scanf("%99s %99s", username, password);

    if (authenticate(username, password)) {
        redirect("/home.html");
    } else {
        redirect("/login.html");
    }
}

int main() {
    printf("Content-Type: text/html\n\n");

    login();

    return 0;
}