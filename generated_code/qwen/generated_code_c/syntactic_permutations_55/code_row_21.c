#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP server functions and structures
typedef struct {
    char *url;
    char *method;
    char *body;
} HttpRequest;

typedef struct {
    int status_code;
    char *content_type;
    char *body;
} HttpResponse;

HttpResponse* create_response(int status_code, const char* content_type, const char* body) {
    HttpResponse* response = (HttpResponse*)malloc(sizeof(HttpResponse));
    response->status_code = status_code;
    response->content_type = strdup(content_type);
    response->body = strdup(body);
    return response;
}

void free_response(HttpResponse* response) {
    free(response->content_type);
    free(response->body);
    free(response);
}

// Mock user database
typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "admin123"},
    {"user", "user123"}
};
int num_users = sizeof(users) / sizeof(User);

// Function declarations
HttpResponse* login(HttpRequest* request);
HttpResponse* do_login(HttpRequest* request);
HttpResponse* index(HttpRequest* request);
HttpResponse* user_page(HttpRequest* request);
HttpResponse* admin_page(HttpRequest* request);

HttpResponse* login(HttpRequest* request) {
    return create_response(200, "text/html", "<form method='post' action='/do_login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form>");
}

HttpResponse* do_login(HttpRequest* request) {
    char username[100], password[100];
    sscanf(request->body, "username=%99[^&]&password=%99s", username, password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (strcmp(username, "admin") == 0) {
                return create_response(302, "text/html", "<meta http-equiv='refresh' content='0;url=/admin_page'>");
            } else {
                return create_response(302, "text/html", "<meta http-equiv='refresh' content='0;url=/user_page'>");
            }
        }
    }
    return create_response(401, "text/plain", "Unauthorized");
}

HttpResponse* index(HttpRequest* request) {
    return create_response(200, "text/html", "<h1>Welcome to the Index Page</h1><a href='/login'>Login</a>");
}

HttpResponse* user_page(HttpRequest* request) {
    return create_response(200, "text/html", "<h1>User Page</h1><p>This is the user page.</p><a href='/index'>Back to index</a>");
}

HttpResponse* admin_page(HttpRequest* request) {
    return create_response(200, "text/html", "<h1>Admin Page</h1><p>This is the admin page.</p><a href='/index'>Back to index</a>");
}

int main() {
    // Simulate HTTP requests
    HttpRequest login_request = {"login", "GET", ""};
    HttpResponse* response = login(&login_request);
    printf("Response: %d %s\n%s\n", response->status_code, response->content_type, response->body);
    free_response(response);

    HttpRequest do_login_request = {"do_login", "POST", "username=admin&password=admin123"};
    response = do_login(&do_login_request);
    printf("Response: %d %s\n%s\n", response->status_code, response->content_type, response->body);
    free_response(response);

    HttpRequest index_request = {"index", "GET", ""};
    response = index(&index_request);
    printf("Response: %d %s\n%s\n", response->status_code, response->content_type, response->body);
    free_response(response);

    HttpRequest user_page_request = {"user_page", "GET", ""};
    response = user_page(&user_page_request);
    printf("Response: %d %s\n%s\n", response->status_code, response->content_type, response->body);
    free_response(response);

    HttpRequest admin_page_request = {"admin_page", "GET", ""};
    response = admin_page(&admin_page_request);
    printf("Response: %d %s\n%s\n", response->status_code, response->content_type, response->body);
    free_response(response);

    return 0;
}