#include <stdio.h>
#include <string.h>

// Mockup for handling HTTP requests and responses
typedef struct {
    const char *method;
    const char *url;
} HttpRequest;

typedef struct {
    int status_code;
    const char *content_type;
    char content[1024];
} HttpResponse;

// Function to simulate the template rendering process
void render_template(const char *template_content, const char *username, HttpResponse *response) {
    snprintf(response->content,
             sizeof(response->content),
             "%s\nHello, %s!",
             template_content,
             username);
}

// Function that is bound to a specific URL pattern
void hello(HttpRequest request, HttpResponse response) {
    // Extracting the username from the URL assuming it's /hello/<username>
    const char *path = strrchr(request.url, '/');
    if (path != NULL && strcmp(path, "/hello/") == 0) {
        path += strlen("/hello/");
        
        // Simulate loading a template file
        const char *template_content = "<html><body><h1>Welcome!</h1>%s</body></html>";
        
        // Render the template with the username
        render_template(template_content, path, &response);
        
        response.status_code = 200;
        response.content_type = "text/html";
    } else {
        snprintf(response.content,
                 sizeof(response.content),
                 "404 Not Found");
                 
        response.status_code = 404;
        response.content_type = "text/plain";
    }
}

// Function to simulate the HTTP request handling
void handle_request(const HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->url, "/hello/<username>") == 0) {
        hello(*request, *response);
    } else {
        snprintf(response->content,
                 sizeof(response->content),
                 "404 Not Found");
                 
        response.status_code = 404;
        response.content_type = "text/plain";
    }
}

int main() {
    // Simulate a user visiting /hello/JohnDoe
    HttpRequest request = {"GET", "/hello/JohnDoe"};
    HttpResponse response;
    
    handle_request(&request, &response);
    
    printf("Status Code: %d\nContent-Type: %s\n\n%s",
           response.status_code,
           response.content_type,
           response.content);

    return 0;
}