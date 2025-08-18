#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_get_request(const char *request) {
    if (strcmp(request, "/login") == 0) {
        login();
    } else if (strcmp(request, "/index") == 0) {
        index();
    } else if (strcmp(request, "/user_page") == 0) {
        user_page();
    } else if (strcmp(request, "/admin_page") == 0) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void handle_post_request(const char *request_body) {
    do_login(request_body);
}

void login() {
    printf("GET /login - Login Page\n");
}

void do_login(const char *credentials) {
    printf("POST /do_login - Processing credentials: %s\n", credentials);
}

void index() {
    printf("GET /index - Welcome to the Index Page\n");
}

void user_page() {
    printf("GET /user_page - User Page Content\n");
}

void admin_page() {
    printf("GET /admin_page - Admin Page Content\n");
}

int main() {
    char request[BUFFER_SIZE];
    
    printf("Enter HTTP request (e.g., GET /login): ");
    fgets(request, BUFFER_SIZE, stdin);
    strtok(request, "\n"); // Remove newline character

    if (strncmp(request, "GET", 3) == 0) {
        handle_get_request(&request[4]);
    } else if (strncmp(request, "POST", 4) == 0) {
        printf("Enter POST body: ");
        char *body = malloc(BUFFER_SIZE);
        fgets(body, BUFFER_SIZE, stdin);
        strtok(body, "\n"); // Remove newline character
        handle_post_request(body);
        free(body);
    } else {
        printf("405 Method Not Allowed\n");
    }

    return 0;
}