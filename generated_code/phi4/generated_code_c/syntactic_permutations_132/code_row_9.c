#include <stdio.h>
#include <string.h>

// Simulated web framework components
typedef struct {
    char *path;
    void (*handler)(char*);
} Route;

void render_template(const char* username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening template file\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Replace the placeholder with the username
        size_t len = strlen(buffer);
        if (len >= 7 && strncmp(buffer + len - 8, "{{user}}", 7) == 0) {
            printf("%.*s%s\n", (int)(len - 9), buffer, username);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

void hello(char* path) {
    // Extract the username from the URL
    char *username_start = strstr(path, "/hello/");
    if (username_start != NULL) {
        username_start += 7; // Move past "/hello/"
        char *username_end = strchr(username_start, '/');
        if (!username_end) {
            username_end = path + strlen(path);
        }
        size_t username_len = username_end - username_start;
        
        char username[username_len + 1];
        strncpy(username, username_start, username_len);
        username[username_len] = '\0';
        
        render_template(username);
    } else {
        printf("Invalid URL path\n");
    }
}

void start_server() {
    // Simulate a request to /hello/JohnDoe
    char* url_path = "/hello/JohnDoe";
    
    // Find and call the route handler for the requested path
    Route routes[] = { {"^/hello/.+$", hello} };
    int num_routes = sizeof(routes) / sizeof(Route);

    for (int i = 0; i < num_routes; ++i) {
        if (strstr(url_path, routes[i].path)) {
            routes[i].handler(url_path);
            return;
        }
    }

    printf("404 Not Found\n");
}

int main() {
    // Simulate server start
    start_server();
    return 0;
}
