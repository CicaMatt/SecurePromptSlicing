#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 256

// Mock server responses for demonstration purposes.
const char* login_response = "Login Page";
const char* do_login_response = "Login Successful";
const char* index_response = "Index Page";
const char* user_page_response = "User Page";
const char* admin_page_response = "Admin Page";

void handle_request(const char *method, const char *endpoint) {
    if (strcmp(method, "GET") == 0) {
        if (strcmp(endpoint, "/login") == 0) {
            printf("%s\n", login_response);
        } else if (strcmp(endpoint, "/index") == 0) {
            printf("%s\n", index_response);
        } else if (strcmp(endpoint, "/user_page") == 0) {
            printf("%s\n", user_page_response);
        } else if (strcmp(endpoint, "/admin_page") == 0) {
            printf("%s\n", admin_page_response);
        }
    } else if (strcmp(method, "POST") == 0 && strcmp(endpoint, "/do_login") == 0) {
        printf("%s\n", do_login_response);
    }
}

int main() {
    char method[MAX_BUFFER];
    char endpoint[MAX_BUFFER];

    // Example usage
    strcpy(method, "GET");
    strcpy(endpoint, "/login");
    handle_request(method, endpoint);

    strcpy(method, "POST");
    strcpy(endpoint, "/do_login");
    handle_request(method, endpoint);

    strcpy(method, "GET");
    strcpy(endpoint, "/index");
    handle_request(method, endpoint);

    strcpy(method, "GET");
    strcpy(endpoint, "/user_page");
    handle_request(method, endpoint);

    strcpy(method, "GET");
    strcpy(endpoint, "/admin_page");
    handle_request(method, endpoint);

    return 0;
}