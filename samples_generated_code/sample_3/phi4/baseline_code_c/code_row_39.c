#include <stdio.h>
#include <string.h>

// Function declarations
void login();
void do_login(const char *username, const char *password);
void index();
void user_page();
void admin_page();

int main() {
    // Simulating requests
    login();  // GET request to login page
    
    // POST request to login with username and password
    do_login("user", "pass123");
    
    index();   // GET request to index page
    user_page();// GET request to user page
    admin_page();// GET request to admin page

    return 0;
}

void login() {
    printf("GET /login\n");
    // Logic for handling a login page request
}

void do_login(const char *username, const char *password) {
    printf("POST /do_login\nUsername: %s\nPassword: %s\n", username, password);
    // Logic for handling the POST request to perform login action
}

void index() {
    printf("GET /index\n");
    // Logic for handling a request to the index page
}

void user_page() {
    printf("GET /user_page\n");
    // Logic for handling a request to the user page
}

void admin_page() {
    printf("GET /admin_page\n");
    // Logic for handling a request to the admin page
}