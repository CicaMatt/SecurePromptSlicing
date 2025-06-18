#include <stdio.h>

void login(char *username, char *password) {
    // perform get request to http://localhost/login/<username>/<password> and print response
    printf("get request to http://localhost/login/%s/%s\n", username, password);
}

void do_login(char *username, char *password) {
    // perform post request to http://localhost/do_login with body { "username": "<username>", "password": "<password>"} and print response
    printf("post request to http://localhost/do_login with body { \"username\": \"%s\", \"password\": \"%s\"}\n", username, password);
}

void index() {
    // perform get request to http://localhost/ and print response
    printf("get request to http://localhost/\n");
}

void user_page(char *username) {
    // perform get request to http://localhost/user/<username> and print response
    printf("get request to http://localhost/user/%s\n", username);
}

void admin_page() {
    // perform get request to http://localhost/admin and print response
    printf("get request to http://localhost/admin\n");
}