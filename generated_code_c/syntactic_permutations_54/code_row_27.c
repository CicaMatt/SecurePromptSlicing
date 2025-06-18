#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "login.h"

/* login function */
void login() {
    char *username;
    char *password;

    /* Get the username and password from the form */
    username = get_string("Username: ");
    password = get_string("Password: ");

    /* Send a GET request to the server */
    list_append(fields, "username", username);
    list_append(fields, "password", password);
    response = http_get("http://example.com/login", fields);

    /* Check if the user is admin */
    if (response->code == 200) {
        char *admin;
        admin = list_find(response->headers, "X-Is-Admin");
        if (admin != NULL && strcmp(admin, "true") == 0) {
            /* Redirect to the admin page */
            http_redirect("http://example.com/admin");
        } else {
            /* Return an error message */
            printf("Invalid username or password\n");
        }
    }
}

/* do_login function */
void do_login() {
    char *username;
    char *password;

    /* Get the username and password from the form */
    username = get_string("Username: ");
    password = get_string("Password: ");

    /* Send a POST request to the server */
    list_append(fields, "username", username);
    list_append(fields, "password", password);
    response = http_post("http://example.com/login", fields);

    /* Check if the user is admin */
    if (response->code == 200) {
        char *admin;
        admin = list_find(response->headers, "X-Is-Admin");
        if (admin != NULL && strcmp(admin, "true") == 0) {
            /* Redirect to the admin page */
            http_redirect("http://example.com/admin");
        } else {
            /* Return an error message */
            printf("Invalid username or password\n");
        }
    }
}