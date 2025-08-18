#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"admin", "admin123"}
};

int num_users = 2;
char session_username[50] = {0};

void redirect(const char *url) {
    printf("Redirecting to %s\n", url);
}

void display_page() {
    const char *html = 
        "<!DOCTYPE html>\n"
        "<html lang='en'>\n"
        "<head>\n"
        "    <meta charset='UTF-8'>\n"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
        "    <title>Index Page</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Welcome to the Index Page</h1>\n"
        "    <a href='/login'>Login</a>\n"
        "</body>\n"
        "</html>";
    printf("%s\n", html);
}

void display_login_page() {
    const char *html = 
        "<!DOCTYPE html>\n"
        "<html lang='en'>\n"
        "<head>\n"
        "    <meta charset='UTF-8'>\n"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
        "    <title>Login Page</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Login</h1>\n"
        "    <form action='/do_login' method='post'>\n"
        "        Username: <input type='text' name='username'><br>\n"
        "        Password: <input type='password' name='password'><br><br>\n"
        "        <input type='submit' value='Login'>\n"
        "    </form>\n"
        "</body>\n"
        "</html>";
    printf("%s\n", html);
}

void display_secret_page() {
    const char *html = 
        "<!DOCTYPE html>\n"
        "<html lang='en'>\n"
        "<head>\n"
        "    <meta charset='UTF-8'>\n"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
        "    <title>Secret Page</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Secret settings</h1>\n"
        "</body>\n"
        "</html>";
    printf("%s\n", html);
}

int check_login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void do_login(const char *username, const char *password) {
    if (check_login(username, password)) {
        strcpy(session_username, username);
        redirect("/secret");
    } else {
        printf("Invalid username or password\n");
        display_login_page();
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        display_page();
        return 0;
    }

    const char *path = argv[1];

    if (strcmp(path, "/") == 0 || strcmp(path, "/index") == 0) {
        display_page();
    } else if (strcmp(path, "/login") == 0) {
        display_login_page();
    } else if (strcmp(path, "/do_login") == 0 && argc > 3) {
        do_login(argv[2], argv[3]);
    } else if (strcmp(path, "/secret") == 0) {
        if (strlen(session_username) > 0) {
            display_secret_page();
        } else {
            printf("Unauthorized access\n");
            display_login_page();
        }
    } else {
        printf("Page not found\n");
    }

    return 0;
}