#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(char *template_file, char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char output[1024];
        snprintf(output, sizeof(output), buffer, username);
        printf("%s", output);
    }
    fclose(file);
}

void hello(char *username) {
    render_template(TEMPLATE_FILE, username);
}

Route routes[] = {
    {"/hello/%s", hello},
};

void route_handler(char *url) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        char pattern[MAX_USERNAME_LENGTH + 10];
        snprintf(pattern, sizeof(pattern), routes[i].url, "");
        if (strncmp(url, pattern, strlen(pattern)) == 0) {
            char username[MAX_USERNAME_LENGTH];
            sscanf(url, routes[i].url, username);
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    char url[256];
    printf("Enter URL: ");
    scanf("%s", url);
    route_handler(url);
    return 0;
}