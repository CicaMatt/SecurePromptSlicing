#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session.username = strdup(username);
    }
}

void show_login_page() {
    printf("<form action='/login' method='post'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void show_secret_page() {
    if (session.username) {
        printf("Secret settings\n");
    } else {
        printf("You are not logged in. <a href='/login'>Login</a>");
    }
}

int main() {
    const char *username = "admin";
    const char *password = "password123";

    do_login(username, password);
    show_secret_page();

    if (session.username) {
        free(session.username);
    }

    return 0;
}