#include <stdio.h>
#include <string.h>

// Simulating Flask-like routing in C
typedef struct {
    char* path;
    void (*handler)(char*);
} Route;

void render_template(const char* username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Template file not found.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, "{{ username }}")) {
            printf("%s%s\n", buffer, username);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

void hello(char* username) {
    render_template(username);
}

Route routes[] = {
    {"/hello/", hello},
};

const char* get_username_from_url(const char* url) {
    const char *start = strstr(url, "/hello/") + strlen("/hello/");
    size_t len = strcspn(start, "/");
    return strndup(start, len);
}

void handle_request(const char* request_path) {
    for (int i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        if (strncmp(request_path, routes[i].path, strlen(routes[i].path)) == 0) {
            const char* username = get_username_from_url(request_path);
            routes[i].handler(username);
            free((void*)username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    // Simulate a user visiting the URL /hello/JohnDoe
    handle_request("/hello/JohnDoe");
    
    return 0;
}
