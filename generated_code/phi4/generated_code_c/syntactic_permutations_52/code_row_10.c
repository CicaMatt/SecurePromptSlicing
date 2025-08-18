#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        // Simulate setting username in session
        printf("Login successful. Setting session...\n");
        redirect("/secret.html");
    } else {
        printf("Invalid credentials.\n");
        redirect("/index.html");
    }
}

void index_page() {
    printf("Index page\n");
    printf("<a href='/login.html'>Login</a>\n");
}

void login_page(char *username, char *password) {
    if (strcmp(username, "") != 0 && strcmp(password, "") != 0) {
        do_login(username, password);
    } else {
        printf("Login page\n");
        printf("<form action='/login' method='post'>\n");
        printf("Username: <input type='text' name='username'><br>\n");
        printf("Password: <input type='password' name='password'><br>\n");
        printf("<input type='submit' value='Login'>\n");
        printf("</form>\n");
    }
}

void secret_page() {
    printf("Secret page\n");
    printf("Secret settings\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "index") == 0) {
            index_page();
        } else if (strcmp(argv[1], "login") == 0 && argc > 3) {
            login_page(argv[2], argv[3]);
        } else if (strcmp(argv[1], "secret") == 0) {
            secret_page();
        }
    } else {
        printf("Usage: %s <index|login [username] [password]|secret>\n", argv[0]);
    }

    return 0;
}