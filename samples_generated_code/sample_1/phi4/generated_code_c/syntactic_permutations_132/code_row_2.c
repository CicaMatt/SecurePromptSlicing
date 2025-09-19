#include <stdio.h>
#include <string.h>

// Simple HTTP server simulation using C
#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*handler)(const char* username);
} Route;

void render_template(const char *username) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Welcome, %s!</h1>\n", username);
    printf("</body></html>\n");
}

void handle_user_route(const char *username) {
    render_template(username);
}

Route routes[] = {
    {"/john", (void (*)(const char*))handle_user_route},
    // Add more routes as needed
};

int find_route_index(char *url, size_t num_routes) {
    for (size_t i = 0; i < num_routes; i++) {
        if (strcmp(url + 1, routes[i].url) == 0) { // Skip the leading '/'
            return i;
        }
    }
    return -1;
}

void handle_request(const char *request) {
    char url[MAX_URL_LENGTH];
    sscanf(request, "GET %s HTTP/1.1", url);

    int route_index = find_route_index(url, sizeof(routes) / sizeof(Route));
    if (route_index != -1) {
        const char *username = routes[route_index].url;
        routes[route_index].handler(username + 1); // Skip the leading '/'
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body>\n<h1>404 Not Found</h1>\n</body></html>\n");
    }
}

int main() {
    const char *request = "GET /john HTTP/1.1";
    handle_request(request);
    
    return 0;
}