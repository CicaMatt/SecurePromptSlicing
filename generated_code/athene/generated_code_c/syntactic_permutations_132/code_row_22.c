#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

void render_template(char *template_file, char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, 1024, file)) {
        size_t pos = 0;
        while ((pos = strstr(buffer + pos, "{{username}}")) != NULL) {
            memmove(pos, pos + 9, strlen(pos + 9) + 1);
            strncpy(pos, username, strlen(username));
            pos += strlen(username);
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello(Request *request) {
    render_template("hello.html", request->username);
}

int main() {
    Request req = {"JohnDoe"};
    char url[] = "/hello/JohnDoe";
    if (strstr(url, "/hello/") == url) {
        hello(&req);
    }
    return 0;
}