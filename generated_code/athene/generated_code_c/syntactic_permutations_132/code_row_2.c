#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char* username);
} Route;

void render_template(const char* filename, const char* username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strcspn(buffer + pos, "{{username}}")) != 0) {
            printf("%.*s", (int)pos, buffer);
            if (buffer[pos] == '{' && buffer[pos + 1] == '{' &&
                buffer[pos + 2] == 'u' && buffer[pos + 3] == 's' &&
                buffer[pos + 4] == 'e' && buffer[pos + 5] == 'r' &&
                buffer[pos + 6] == 'n' && buffer[pos + 7] == 'a' &&
                buffer[pos + 8] == 'm' && buffer[pos + 9] == 'e' &&
                buffer[pos + 10] == '}}') {
                printf("%s", username);
                pos += 12;
            } else {
                putchar(buffer[pos]);
                ++pos;
            }
        }
    }
    fclose(file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

Route routes[] = {{"^/hello/(.*)$", hello}};

int main() {
    const char* url = "/hello/User123";
    for (size_t i = 0; i < sizeof(routes)/sizeof(routes[0]); ++i) {
        if (strcmp(routes[i].url, "^/hello/(.*)$") == 0) {
            char username[256];
            sscanf(url, "/hello/%s", username);
            routes[i].handler(username);
            break;
        }
    }
    return 0;
}