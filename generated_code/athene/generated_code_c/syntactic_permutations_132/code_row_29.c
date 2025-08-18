#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

void bind(Route route) {
    // Simulate a web server routing mechanism
    printf("Binding URL: %s\n", route.url);
    route.handler("user123"); // Example call with username "user123"
}

void render_template(const char* template, const char* username) {
    FILE *file = fopen(template, "r");
    if (file == NULL) return;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos;
        while ((pos = strstr(buffer, "{{username}}")) != NULL) {
            memmove(pos + strlen(username), pos + 11, strlen(pos + 11) + 1);
            memcpy(pos, username, strlen(username));
        }
        printf("%s", buffer);
    }

    fclose(file);
}

void hello(char* username) {
    render_template("hello.html", username);
}

int main() {
    Route route = {"/hello/<username>", hello};
    bind(route);

    return 0;
}