#include <stdio.h>
#include <string.h>

// Function prototypes
void register_route(const char* url, void (*func)(const char*));
char* escape_html(const char* input);
void hello_user(const char* username);

// Route mapping structure
typedef struct {
    const char* url;
    void (*handler)(const char*);
} route_t;

static route_t routes[10];
static int route_count = 0;

// Function to register a URL and its corresponding handler function
void register_route(const char* url, void (*func)(const char*)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = func;
        route_count++;
    }
}

// Function to escape HTML special characters
char* escape_html(const char* input) {
    static char output[256];
    const char* src = input;
    char* dest = output;

    while (*src) {
        switch (*src) {
            case '&': *dest++ = '&'; *dest++ = 'a'; *dest++ = 'm'; *dest++ = 'p'; *dest++ = ';'; break;
            case '<': *dest++ = '&'; *dest++ = 'l'; *dest++ = 't'; *dest++ = ';'; break;
            case '>': *dest++ = '&'; *dest++ = 'g'; *dest++ = 't'; *dest++ = ';'; break;
            case '"': *dest++ = '&'; *dest++ = 'q'; *dest++ = 'u'; *dest++ = 'o'; *dest++ = 't'; *dest++ = ';'; break;
            default:  *dest++ = *src; break;
        }
        src++;
    }
    *dest = '\0';
    return output;
}

// Function to handle the /username route
void hello_user(const char* username) {
    printf("Hello %s\n", escape_html(username));
}

// Simulate a request handling mechanism
void handle_request(const char* url, const char* params) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(params);
            return;
        }
    }
    printf("404 Not Found\n");
}

// Main function to register routes and simulate a request
int main() {
    // Register the /username route
    register_route("/username", hello_user);

    // Simulate navigating to /username with parameter "John Doe"
    handle_request("/username", "John Doe");

    return 0;
}