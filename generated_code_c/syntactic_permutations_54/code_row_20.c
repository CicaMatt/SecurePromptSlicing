#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylibrary.h"

void login(char *username, char *password) {
    char form_html[1024];
    sprintf(form_html, "<html><body><h2>Login</h2>"
                       "<form action='/login' method='post'>"
                       "Username: <input type='text' name='username'><br>"
                       "Password: <input type='password' name='password'><br>"
                       "<input type='submit' value='Submit'>"
                       "</form></body></html>");
    printf("Content-Type: text/html\n\n");
    printf(form_html);
}

void login_post(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        redirect("/admin_page");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h2>Login failed</h2></body></html>");
    }
}