#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

void render_template(char* template_file, char* username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char out[1024] = "";
        size_t pos = 0;
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '{' && buffer[i+1] == '{') {
                i += 2;
                while (buffer[i] != '}' || buffer[i+1] != '}') {
                    out[pos++] = buffer[i++];
                }
                out[pos] = '\0';
                printf("%s", username);
                i += 2;
            } else {
                printf("%c", buffer[i]);
            }
        }
    }
    fclose(file);
}

void user_page(char* username) {
    render_template("template.html", username);
}

void route_handler(Route *route, char* path) {
    if (strcmp(route->url, path) == 0) {
        route->handler(path + strlen(route->url));
    }
}

int main() {
    Route routes[] = {{"user/", user_page}};
    char path[1024];
    scanf("%s", path);
    for (size_t i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        route_handler(&routes[i], path);
    }
    return 0;
}