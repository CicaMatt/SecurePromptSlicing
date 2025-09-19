#include <stdio.h>
#include <string.h>

// Simulated session storage
#define SESSION_SIZE 256
char session[SESSION_SIZE] = {0};

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(session, username, SESSION_SIZE - 1);
        redirect("/secret");
        return 1;
    }
    return 0;
}

void show_index_page() {
    printf("Index Page\n");
    printf("<a href='/login'>Login</a>\n");
}

void show_login_page(const char *username) {
    printf("Login Page\n");
    if (strlen(username) > 0) {
        printf("Invalid username or password!\n");
    }
    printf("<form action='/login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
}

void show_secret_page() {
    if (strcmp(session, "admin") == 0) {
        printf("Secret settings\n");
    } else {
        redirect("/login");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_index_page();
        return 0;
    }

    const char *page = argv[1];

    if (strcmp(page, "index") == 0) {
        show_index_page();
    } else if (strcmp(page, "login") == 0) {
        if (argc < 4 || strcmp(argv[2], "POST") != 0) {
            show_login_page("");
        } else {
            do_login(argv[3], argv[4]);
        }
    } else if (strcmp(page, "secret") == 0) {
        show_secret_page();
    }

    return 0;
}