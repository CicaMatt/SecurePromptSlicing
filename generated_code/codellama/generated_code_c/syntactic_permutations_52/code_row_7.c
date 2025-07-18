#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h>

#include <netdb.h>

#include <arpa/inet.h>



#define SECRET_PAGE  "secret_page.html"

#define INDEX_PAGE "index.html"



// Login credentials.

const char* user = "admin";

const char* pwd = "password";

char username[50];

char password[50];

int isValidLogin(void);



void do_login() {

    if (isValidLogin()) {

        // Set the session.

        setcookie("username", username, time() + 3600 * 24);

        // Redirect to secret page.

        header("Location: " SECRET_PAGE);

    }

}



int isValidLogin(void) {

    if (!strcmp(user, username))

        return 1;

    return 0;

}



// Login Page.

void login() {

    printf("<form action=\"login.html\">

            <div>Username:</div>

            <input type=\"text\" name=\"username\" value = \"%s\"><br>

            <div>Password:</div>

            <input type=\"password\" name=\"password\" value = \"%s\"><br><br>

            <input type=\"submit\" value=\"Submit\">

          </form>", username, password);

}



// Secret Page.

void secret() {

    printf("<p>Secret settings</p>");

}



// Index page.

void index() {

    printf("<a href=\"login.html\">Login</a>");

}
