#include <stdio.h>
#include <string.h>

// Simulate a basic structure for HTTP requests and responses.
typedef struct {
    const char* method;
    const char* path;
    const char* body;
} HttpRequest;

typedef struct {
    int status_code;
    const char* content_type;
    const char* body;
} HttpResponse;

// Function to generate login form
HttpResponse handle_login_get(HttpRequest request) {
    if (strcmp(request.method, "GET") == 0 && strcmp(request.path, "/login") == 0) {
        return (HttpResponse){200, "text/html", "<html><body>"
                                  "<form action='/do_login' method='POST'>"
                                  "Username: <input type='text' name='username'><br>"
                                  "Password: <input type='password' name='password'><br>"
                                  "<input type='submit' value='Login'>"
                                  "</form></body></html>"};
    }
    return (HttpResponse){404, "text/plain", "Not Found"};
}

// Function to handle login logic
HttpResponse handle_do_login_post(HttpRequest request) {
    if (strcmp(request.method, "POST") == 0 && strcmp(request.path, "/do_login") == 0) {
        const char* username = strstr(request.body, "username=") + strlen("username=");
        const char* password_end = strstr(username, "&");
        const char* password_start = strstr(username, "password=") + strlen("password=");
        char username_str[256], password_str[256];

        if (password_end)
            strncpy(username_str, username, password_end - username);
        else
            strcpy(username_str, username);

        if (*password_start != '\0') {
            strncpy(password_str, password_start + 1, password_end ? password_end - password_start - 1 : strlen(password_start) - 1);
            password_str[password_end ? password_end - password_start - 1 : strlen(password_start) - 1] = '\0';
        }

        if (strcmp(username_str, "admin") == 0 && strcmp(password_str, "admin") == 0) {
            return (HttpResponse){302, "text/html", "<html><body>"
                                          "Redirecting to admin page...</body></html>"};
        }
    }
    return (HttpResponse){200, "text/plain", "Login failed or not authorized"};
}

// Main function for handling requests
void handle_request(HttpRequest request) {
    HttpResponse response;

    if (strcmp(request.path, "/login") == 0) {
        response = handle_login_get(request);
    } else if (strcmp(request.path, "/do_login") == 0) {
        response = handle_do_login_post(request);
    } else {
        response = (HttpResponse){404, "text/plain", "Not Found"};
    }

    printf("HTTP/1.1 %d\nContent-Type: %s\nContent-Length: %lu\n\n%s",
           response.status_code,
           response.content_type,
           strlen(response.body),
           response.body);
}

int main() {
    // Simulate GET request for login
    HttpRequest get_login_request = {"GET", "/login", NULL};
    handle_request(get_login_request);

    printf("\n---\n");

    // Simulate POST request for logging in as admin
    HttpRequest post_admin_request = {"POST", "/do_login", "username=admin&password=admin"};
    handle_request(post_admin_request);

    printf("\n---\n");

    // Simulate POST request with wrong credentials
    HttpRequest post_wrong_credentials_request = {"POST", "/do_login", "username=user&password=pass"};
    handle_request(post_wrong_credentials_request);
    
    return 0;
}