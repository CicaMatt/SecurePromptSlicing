#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//login page code
void loginPage(void) {
    printf("<html><head></head><body>\n");
    printf("<form action=\"./do_login\" method=\"post\">\n");
    printf("<label for=\"username\">Username:</label><br>\n");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>\n");
    printf("<label for=\"password\">Password:</label><br>\n");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form></body></html>\n");
}

//do_login page code
void doLogin(char *username, char *password) {
    if (strcmp(username,"admin")==0 && strcmp(password,"secret")==0){
        redirect("./secret");
    }else{
        printf("<html><head></head><body>Wrong username or password</body></html>\n");
    }
}

//secret page code
void secretPage(char *username) {
    printf("<html><head></head><body>\n");
    printf("Welcome to the secret page, %s!",username);
    printf("</body></html>\n");
}

//redirect function
void redirect(const char *url){
    printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", url);
}

//main function
int main() {
    //login page code
    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/") == 0) {
        loginPage();
    } else if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0 && strcmp(getenv("PATH_INFO"), "/do_login") == 0) {
        char username[128];
        char password[128];
        sscanf(getenv("QUERY_STRING"), "username=%s&password=%s", username, password);
        doLogin(username, password);
    } else if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/secret") == 0) {
        char *username = getenv("HTTP_COOKIE");
        secretPage(username);
    } else {
        printf("<html><head></head><body>404 Not Found</body></html>\n");
    }
}