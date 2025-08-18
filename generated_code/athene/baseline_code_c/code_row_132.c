#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *username;
} Request;

void render_template(char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        printf("Template file not found\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t pos = 0;
        while ((pos = strstr(line, "{{ username }}") - line) != (size_t)-1) {
            memmove(line + pos, line + pos + 13, strlen(line + pos + 13) + 1);
            strncpy(line + pos, username, strlen(username));
        }
        printf("%s", line);
    }
    fclose(file);
}

void hello(Request *request) {
    render_template(TEMPLATE_FILE, request->username);
}

int main() {
    Request req = { .username = "John Doe" };
    hello(&req);
    return 0;
}