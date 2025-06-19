#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int login() {
    printf("Content-type: text/html\n\n");
    printf("<form action=\"do_login\" method=\"POST\">");
    printf("Enter username: ");
    printf("<input type=\"text\" name=\"username\"><br />");
    printf("Enter password: ");
    printf("<input type=\"password\" name=\"password\"><br />");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
}

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123")) {
        redirect("/admin_page");
    } else {
        printf("Content-type: text/html\n\n");
        printf("<h1>Error!</h1>");
    }
}