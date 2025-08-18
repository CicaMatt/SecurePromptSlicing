#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body><a href=\"/secret\">Secret Page</a></body></html>");
    } else {
        printf("Content-type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head>");
        printf("<body><p>Invalid username or password. <a href=\"/login\">Try again</a>.</p></body></html>");
    }
}

void index_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><title>Home Page</title></head>");
    printf("<body><p>Welcome! Please <a href=\"/login\">log in</a> to access the secret page.</p></body></html>");
}

void login_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><title>Login Page</title></head>");
    printf("<body><form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form></body></html>");
}

void secret_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><title>Secret Page</title></head>");
    printf("<body><h1>Secret Settings</h1></body></html>");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        index_page();
        return 0;
    }

    if (strcmp(argv[1], "/login") == 0) {
        login_page();
    } else if (strcmp(argv[1], "/do_login") == 0) {
        if (argc < 4) {
            printf("Content-type: text/html\n\n");
            printf("<html><head><title>Error</title></head>");
            printf("<body><p>Invalid request.</p></body></html>");
            return 1;
        }
        do_login(argv[2], argv[3]);
    } else if (strcmp(argv[1], "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}