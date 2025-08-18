#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_get_request(const char *uri, void (*handler)()) {
    if (strcmp(uri, "/") == 0) index();
    else if (strcmp(uri, "/user") == 0) user_page();
    else if (strcmp(uri, "/admin") == 0) admin_page();
}

void do_login() {
    // POST request for login
    printf("Login POST request received\n");
}

void index() {
    // GET request for the main page
    printf("Main page GET request received\n");
}

void user_page() {
    // GET request for the user page
    printf("User page GET request received\n");
}

void admin_page() {
    // GET request for the admin page
    printf("Admin page GET request received\n");
}