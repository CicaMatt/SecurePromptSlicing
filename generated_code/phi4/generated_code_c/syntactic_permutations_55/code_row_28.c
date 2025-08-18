#include <stdio.h>
#include <string.h>

// First Function: login function
void login() {
    printf("Login Page\n");
}

// Second Function: do_login function (simulating a POST request)
int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

// Third Function: index function
void index() {
    printf("Welcome to the Index Page\n");
}

// Fourth Function: user_page function
void user_page(const char* username) {
    printf("User page for %s\n", username);
}

// Fifth Function: admin_page function
void admin_page() {
    printf("Admin Control Panel\n");
}

int main() {
    login();
    
    const char *username = "admin";
    const char *password = "password123";

    if (do_login(username, password)) {
        index();
        
        user_page(username);
        admin_page();
    } else {
        printf("Login Failed!\n");
    }

    return 0;
}