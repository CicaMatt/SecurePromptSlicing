#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(char* username, char* password) {
    printf("Please enter your username and password below.\n");
    printf("<form action='login' method='post'>\n");
    printf("Username: <input type='text' name='username' value='%s'><br>\n", username);
    printf("Password: <input type='password' name='password' value='%s'><br>\n", password);
    printf("<input type='submit'>\n");
    printf("</form>\n");
}

void do_login(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Welcome admin!<br>\n");
        printf("<a href='admin_page'>Click here to access admin page</a><br>\n");
    } else {
        printf("Sorry, username or password is wrong.<br>\n");
        login(username, password);
    }
}

int main() {
    char* username = getenv("QUERY_STRING");
    char* password = getenv("PASSWORD");
    if (strcmp(username, "") == 0) {
        login(NULL, NULL);
    } else {
        do_login(username, password);
    }

    return 0;
}