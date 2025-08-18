#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"admin", "password"}, {"user1", "pass1"}};
int login_state = 0; // 0: not logged in, 1: user logged in, 2: admin logged in

void get_request(const char *path) {
    if (strcmp(path, "/login") == 0) {
        printf("Login Page\n");
    } else if (strcmp(path, "/index") == 0 && login_state > 0) {
        index();
    } else if (strcmp(path, "/user_page") == 0 && login_state == 1) {
        user_page();
    } else if (strcmp(path, "/admin_page") == 0 && login_state == 2) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void post_request(const char *path, const char *username, const char *password) {
    if (strcmp(path, "/do_login") == 0) {
        for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
            if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                login_state = (strcmp(username, "admin") == 0) ? 2 : 1;
                printf("Login Successful\n");
                return;
            }
        }
        printf("Invalid Username or Password\n");
    } else {
        printf("404 Not Found\n");
    }
}

void index() {
    if (login_state == 1) {
        printf("Welcome User Page!\n");
    } else if (login_state == 2) {
        printf("Welcome Admin Page!\n");
    }
}

void user_page() {
    printf("User-specific content.\n");
}

void admin_page() {
    printf("Admin-specific content.\n");
}

int main() {
    char method[10], path[100];
    
    // Example GET request to login
    strcpy(method, "GET");
    strcpy(path, "/login");
    get_request(path);
    
    // Example POST request for login
    strcpy(method, "POST");
    strcpy(path, "/do_login");
    post_request(path, "admin", "password");

    // Example GET request to index after login
    strcpy(method, "GET");
    strcpy(path, "/index");
    get_request(path);

    // Example GET requests to user and admin pages
    strcpy(method, "GET");
    strcpy(path, "/user_page");
    get_request(path);
    
    strcpy(method, "GET");
    strcpy(path, "/admin_page");
    get_request(path);

    return 0;
}