#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP server framework (for demonstration purposes)
typedef struct {
    const char *method;
    const char *path;
    const char *query;
} Request;

typedef struct {
    int status;
    const char *headers[2];
    const char *body;
} Response;

void handle_request(Request *req, Response *res);

// Mock database functions
int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
    return 1; // Return 1 for success
}

// Function to render the main page with messages
void render_main_page(Response *res, const char *messages) {
    res->status = 200;
    res->headers[0] = "Content-Type: text/html";
    res->headers[1] = NULL;
    res->body = malloc(strlen(messages) + 1);
    strcpy((char *)res->body, messages);
}

// Function to parse query parameters
int parse_query(const char *query, const char *key, char *value, size_t value_len) {
    if (query == NULL || key == NULL || value == NULL) return 0;
    char *param = strstr(query, key);
    if (param == NULL) return 0;
    param += strlen(key); // Move past the key
    if (*param != '=') return 0;
    param++; // Move past the '='
    size_t len = strcspn(param, "&");
    strncpy(value, param, value_len > len ? len : value_len - 1);
    value[len] = '\0';
    return 1;
}

// Route handler for /post
void handle_post(Request *req, Response *res) {
    if (strcmp(req->method, "POST") != 0) {
        res->status = 405; // Method Not Allowed
        res->headers[0] = "Allow: POST";
        res->headers[1] = NULL;
        res->body = "Method Not Allowed";
        return;
    }

    char username[256];
    char message[256];
    if (parse_query(req->query, "username", username, sizeof(username)) &&
        parse_query(req->query, "message", message, sizeof(message))) {
        if (insert_user_message_in_db(username, message) == 1) {
            res->status = 303; // See Other
            res->headers[0] = "Location: /";
            res->headers[1] = NULL;
            res->body = "";
        } else {
            res->status = 500; // Internal Server Error
            res->headers[0] = "Content-Type: text/plain";
            res->headers[1] = NULL;
            res->body = "Failed to insert message into the database.";
        }
    } else {
        res->status = 400; // Bad Request
        res->headers[0] = "Content-Type: text/plain";
        res->headers[1] = NULL;
        res->body = "Missing username or message in request.";
    }
}

// Route handler for /
void handle_root(Request *req, Response *res) {
    if (strcmp(req->method, "GET") != 0) {
        res->status = 405; // Method Not Allowed
        res->headers[0] = "Allow: GET";
        res->headers[1] = NULL;
        res->body = "Method Not Allowed";
        return;
    }

    const char *messages = "<h1>Messages</h1><ul><li>User1: Hello, World!</li></ul>";
    render_main_page(res, messages);
}

// Main request handler
void handle_request(Request *req, Response *res) {
    if (strcmp(req->path, "/post") == 0) {
        handle_post(req, res);
    } else if (strcmp(req->path, "/") == 0) {
        handle_root(req, res);
    } else {
        res->status = 404; // Not Found
        res->headers[0] = "Content-Type: text/plain";
        res->headers[1] = NULL;
        res->body = "Not Found";
    }
}

int main() {
    Request req = {"POST", "/post", "username=JohnDoe&message=Hello%2C+World!"};
    Response res;

    handle_request(&req, &res);

    printf("Status: %d\n", res.status);
    for (int i = 0; res.headers[i] != NULL; i++) {
        printf("%s\n", res.headers[i]);
    }
    if (res.body) {
        printf("%s\n", res.body);
        free((char *)res.body);
    }

    return 0;
}