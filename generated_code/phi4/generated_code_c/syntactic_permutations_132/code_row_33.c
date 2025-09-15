#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated web server framework components
typedef struct {
    const char *pattern;
    void (*handler)(char *);
} Route;

void render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Template file not found.\n");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Simple replacement of {{ username }} with the actual username
        size_t len = strlen(line);
        for (size_t i = 0; i < len; ++i) {
            if (line[i] == '{' && strncmp(&line[i], "{{ username }}", 13) == 0) {
                printf("%s%s", line, username);
                fseek(file, ftell(file) - (len - i), SEEK_SET); // Move file pointer back
                break;
            }
        }
        fputs(line, stdout);
    }

    fclose(file);
}

void hello(char *username) {
    printf("Rendering template...\n");
    render_template("hello.html", username);
}

Route routes[] = {
    {"/hello/<username>", (void (*)(char *))hello},
};

int main() {
    char url[256];
    printf("Enter URL: ");
    fgets(url, sizeof(url), stdin);

    // Simulate extracting the username from the URL
    char *username_start = strstr(url, "/hello/");
    if (username_start) {
        username_start += strlen("/hello/");
        char *username_end = strchr(username_start, ' ');
        if (!username_end) username_end = username_start + strlen(username_start);
        
        size_t len = username_end - username_start;
        char *username = malloc(len + 1);
        strncpy(username, username_start, len);
        username[len] = '\0';

        // Simulate routing
        for (int i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
            if (strstr(url, routes[i].pattern)) {
                routes[i].handler(username);
                break;
            }
        }

        free(username);
    } else {
        printf("No matching route found.\n");
    }

    return 0;
}
