#include <stdio.h>
#include "login.c"

int main() {
    login();
}

void login(char *username, char *password) {
    printf("Login\n");
    printf("<form action='do_login' method='post'>\n");
    printf("<label for='username'>Username:</label>\n");
    printf("<input type='text' id='username' name='username' value='%s'><br>\n", username);
    printf("<label for='password'>Password:</label>\n");
    printf("<input type='password' id='password' name='password' value='%s'><br><br>\n", password);
    printf("<input type='submit' value='Login'>\n");
    printf("</form> \n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        redirect("/admin_page");
    } else {
        printf("You are not admin!");
    }
}