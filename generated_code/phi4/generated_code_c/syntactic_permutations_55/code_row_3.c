#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User user = {"admin", "password"};

void handle_request(const char *request) {
    if (strncmp(request, "GET /login", 10) == 0) {
        login();
    } else if (strncmp(request, "POST /do_login", 14) == 0) {
        do_login(request);
    } else if (strncmp(request, "GET /index", 10) == 0) {
        index();
    } else if (strncmp(request, "GET /user_page", 14) == 0) {
        user_page();
    } else if (strncmp(request, "GET /admin_page", 15) == 0) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void login() {
    printf("Login Page\n");
    printf("<form method='POST' action='/do_login'>\n"
           "Username: <input type='text' name='username'><br>\n"
           "Password: <input type='password' name='password'><br>\n"
           "<input type='submit' value='Login'>\n"
           "</form>\n");
}

void do_login(const char *request) {
    char username[50];
    char password[50];

    sscanf(request, "POST /do_login username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
        printf("Login Successful\n");
    } else {
        printf("Login Failed\n");
    }
}

void index() {
    printf("Welcome to the Index Page!\n");
}

void user_page() {
    printf("Welcome to the User Page!\n");
}

void admin_page() {
    printf("Welcome to the Admin Page!\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <request>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);
    return EXIT_SUCCESS;
}