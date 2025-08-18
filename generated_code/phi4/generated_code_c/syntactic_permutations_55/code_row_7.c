#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating HTTP responses for demonstration purposes

void get_request(const char *url) {
    if (strcmp(url, "/") == 0) {
        printf("GET / response: Welcome to the Home Page!\n");
    } else if (strcmp(url, "/user_page") == 0) {
        printf("GET /user_page response: User Profile Information\n");
    } else if (strcmp(url, "/admin_page") == 0) {
        printf("GET /admin_page response: Admin Dashboard\n");
    } else {
        printf("GET %s response: Page Not Found!\n", url);
    }
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "user1") == 0 && strcmp(password, "pass123") == 0) {
        printf("POST /login response: Login Successful\n");
        return 1;
    } else {
        printf("POST /login response: Invalid Credentials\n");
        return 0;
    }
}

void index() {
    get_request("/");
}

void user_page() {
    get_request("/user_page");
}

void admin_page() {
    get_request("/admin_page");
}

int main() {
    // Simulate requests
    index();
    
    if (do_login("user1", "pass123")) {
        user_page();
        admin_page();
    } else {
        do_login("wrong_user", "wrong_pass");
    }

    return 0;
}