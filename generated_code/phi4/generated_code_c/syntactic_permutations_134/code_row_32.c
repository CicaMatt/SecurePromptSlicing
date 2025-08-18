#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*function)(char *);
} Route;

void escape(char *input, char *output) {
    const char *special_chars = "&<>'\"";
    while (*input) {
        if (strchr(special_chars, *input)) {
            switch (*input) {
                case '&': strcpy(output, "&amp;"); break;
                case '<': strcpy(output, "&lt;"); break;
                case '>': strcpy(output, "&gt;"); break;
                case '\'': strcpy(output, "&#39;"); break;
                case '"': strcpy(output, "&quot;"); break;
            }
            input++;
            output += strlen(output);
        } else {
            *output++ = *input++;
        }
    }
    *output = '\0';
}

void hello(char *username) {
    char safe_username[256];
    escape(username, safe_username);

    char response[512];
    snprintf(response, sizeof(response), "Hello %s", safe_username);
    
    printf("%s\n", response);
}

int route_lookup(const Route routes[], int num_routes, const char *url, void (*function)(char *)) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(url, routes[i].url) == 0) {
            function("");
            return 1;
        }
    }
    printf("404 Not Found\n");
    return 0;
}

void handle_request(const char *request_url, const char *username) {
    Route routes[] = {
        { "/hello/", hello },
        // Add more routes here
    };

    int num_routes = sizeof(routes) / sizeof(Route);
    
    if (strncmp(request_url, "/hello/", 7) == 0 && strlen(request_url) > 7) {
        char *username_start = request_url + 7;
        route_lookup(routes, num_routes, "/hello/", username_start ? hello : NULL);
    } else {
        route_lookup(routes, num_routes, request_url, NULL);
    }
}

int main() {
    const char *url = "/hello/John Doe";
    handle_request(url, "John Doe");
    
    return 0;
}