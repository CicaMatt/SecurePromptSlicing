#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} request_t;

char* render_template(const char *template, const char *username) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template, username);
    return buffer;
}

void hello(request_t *req) {
    if (req->username == NULL || strlen(req->username) == 0) {
        printf("Error: Username is required.\n");
        return;
    }

    const char *template = "<html><body>Hello, %s!</body></html>";
    char *response = render_template(template, req->username);
    
    printf("%s\n", response);
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username_start = url + 7;
        request_t req = { .username = strdup(username_start) };
        
        hello(&req);

        free(req.username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/Alice");
    return 0;
}