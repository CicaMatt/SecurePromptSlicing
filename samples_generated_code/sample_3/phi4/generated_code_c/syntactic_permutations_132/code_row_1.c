#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple web server framework and templates

typedef struct {
    const char *username;
} Request;

typedef struct {
    const char *content;
} Response;

void render_template(const char *template_name, const char *var_value) {
    if (strcmp(template_name, "hello.html") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Hello, %s!</h1>", var_value);
        printf("</body></html>\n");
    }
}

void handle_request(Request *req, Response *res) {
    char username[256];
    snprintf(username, sizeof(username), "%s", req->username);

    render_template("hello.html", username);
}

int main() {
    // Simulating a request to /hello/<username>
    Request req = {"/hello/JohnDoe"};
    Response res;

    handle_request(&req, &res);

    return 0;
}


This C code simulates handling a web server request and rendering a template. It assumes the use of a simple framework where `Request` contains the URL path and any dynamic segments like `/hello/<username>`, and `Response` is used to store the response content (though it's not fully utilized here). The function `render_template` simulates rendering an HTML page, inserting a username into the template.