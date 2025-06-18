/* Import necessary libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* User structure definition */
typedef struct {
    char* username;
    char* email;
    int ssn;
} User;

/* Function to generate a user object */
User* create_user(char* username, char* email, int ssn) {
    /* Create user structure */
    User* new_user = (User*)malloc(sizeof(User));

    /* Set user fields */
    new_user->username = username;
    new_user->email = email;
    new_user->ssn = ssn;

    /* Return user structure */
    return new_user;
}

/* Function to generate the html page */
void create_html(User* user) {
    /* Create html code */
    char* html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>User</title></head><body>";

    /* Add username to html */
    html += "<h1>Username: ";
    html += user->username;

    /* Add email to html */
    html += "</h1><p>Email: ";
    html += user->email;

    /* Add social security number to html */
    html += "</p><p>Social Security Number: ";
    char* ssn_string = (char*)malloc(sizeof(int));
    sprintf(ssn_string, "%d", user->ssn);
    html += ssn_string;

    /* End html */
    html += "</p></body></html>";

    /* Print html code */
    printf("%s\n", html);
}

/* Function to handle requests */
int main(void) {
    /* Create user structure */
    User* user = create_user("John Doe", "johndoe@email.com", 123456789);

    /* Generate html page */
    create_html(user);

    /* Return success code */
    return EXIT_SUCCESS;
}