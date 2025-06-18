#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void index();
void login();
void do_login(char *username, char *password);

int main() {
    index();
    return 0;
}

void index() {
    printf("Welcome to the secret page\n");
    printf("<a href=\\"./login.html\\">Login</a>\n");
}

void login() {
    char username[1024];
    char password[1024];

    printf("Please enter your credentials:\n");
    printf("<form method=\\"post\\">\n");
    printf("Username: <input type=\\"text\\" name=\\"username\\"><br>\n");
    printf("Password: <input type=\\"password\\" name=\\"password\\"><br><br>\n");
    printf("<input type=\\"submit\\" value=\\"Log in\\">\n");
    printf("</form>\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret123") == 0) {
        set_session_variable("username", username);
        redirect("./index.html");
    } else {
        printf("Invalid credentials\n");
    }
}