#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock definitions for HTTP request handling (for demonstration purposes)
typedef struct {
    char* method;
    char* path;
} HttpRequest;

typedef struct {
    int status_code;
    const char* body;
} HttpResponse;

// Function prototypes
HttpResponse login(HttpRequest req);
HttpResponse do_login(HttpRequest req, const char* username, const char* password);
HttpResponse index(HttpRequest req);
HttpResponse user_page(HttpRequest req, const char* username);

int main() {
    // Example usage (in a real scenario, these would come from an HTTP server)
    HttpRequest login_req = { .method = "GET", .path = "/login" };
    HttpResponse res1 = login(login_req);
    printf("Login Response: %d - %s\n", res1.status_code, res1.body);

    // Simulating a POST request with credentials
    HttpRequest do_login_req = { .method = "POST", .path = "/do_login" };
    HttpResponse res2 = do_login(do_login_req, "user123", "password");
    printf("Do Login Response: %d - %s\n", res2.status_code, res2.body);

    HttpRequest index_req = { .method = "GET", .path = "/" };
    HttpResponse res3 = index(index_req);
    printf("Index Response: %d - %s\n", res3.status_code, res3.body);

    HttpRequest user_page_req = { .method = "GET", .path = "/user_page" };
    HttpResponse res4 = user_page(user_page_req, "user123");
    printf("User Page Response: %d - %s\n", res4.status_code, res4.body);

    return 0;
}

HttpResponse login(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/login") == 0) {
        return (HttpResponse){ .status_code = 200, .body = "Login Page" };
    }
    return (HttpResponse){ .status_code = 404, .body = "Not Found" };
}

HttpResponse do_login(HttpRequest req, const char* username, const char* password) {
    if (strcmp(req.method, "POST") == 0 && strcmp(req.path, "/do_login") == 0) {
        // Simplified authentication check
        if (strcmp(username, "user123") == 0 && strcmp(password, "password") == 0) {
            return (HttpResponse){ .status_code = 200, .body = "Login Successful" };
        }
    }
    return (HttpResponse){ .status_code = 401, .body = "Unauthorized" };
}

HttpResponse index(HttpRequest req) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/") == 0) {
        return (HttpResponse){ .status_code = 200, .body = "Welcome to the Index Page" };
    }
    return (HttpResponse){ .status_code = 404, .body = "Not Found" };
}

HttpResponse user_page(HttpRequest req, const char* username) {
    if (strcmp(req.method, "GET") == 0 && strcmp(req.path, "/user_page") == 0) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "User Page for %s", username);
        return (HttpResponse){ .status_code = 200, .body = buffer };
    }
    return (HttpResponse){ .status_code = 404, .body = "Not Found" };
}