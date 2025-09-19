#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* filename, const char* username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("<p>Username: %s</p>", username);
}

void user_handler(const char* username) {
    render_template("template.html", username);
}

Route routes[] = {{"<username>", user_handler}};

void route_request(const char* url, const char* username) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    const char* requested_url = "<username>";
    const char* username = "JohnDoe";
    route_request(requested_url, username);
    return 0;
}