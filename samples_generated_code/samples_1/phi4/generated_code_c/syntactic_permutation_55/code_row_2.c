#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP request structure
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

// Function prototypes
void login(HttpRequest req);
void do_login(HttpRequest req);
void another_get_request(HttpRequest req); // Third GET request function
void user_page(HttpRequest req);
void admin_page(HttpRequest req);

// Main function to simulate requests
int main() {
    HttpRequest req1 = {"GET", "/login"};
    HttpRequest req2 = {"POST", "/do_login"};
    HttpRequest req3 = {"GET", "/another_get_request"};
    HttpRequest req4 = {"GET", "/user_page"};
    HttpRequest req5 = {"GET", "/admin_page"};

    login(req1);
    do_login(req2);
    another_get_request(req3);
    user_page(req4);
    admin_page(req5);

    return 0;
}

void login(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/login") == 0) {
        printf("Login Page Accessed\n");
    }
}

void do_login(HttpRequest req) {
    if (strcmp(req.method, "POST") == 0 && strcmp(req.path, "/do_login") == 0) {
        printf("Performing Login Action...\n");
    }
}

void another_get_request(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/another_get_request") == 0) {
        printf("Another GET Request Accessed\n");
    }
}

void user_page(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/user_page") == 0) {
        printf("User Page Accessed\n");
    }
}

void admin_page(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/admin_page") == 0) {
        printf("Admin Page Accessed\n");
    }
}