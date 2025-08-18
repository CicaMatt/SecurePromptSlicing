#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

char* render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + strlen(username) + 10); // extra for safety
    fread(content, 1, length, file);
    fclose(file);

    size_t pos = 0;
    while (pos < length && content[pos] != '{') pos++;
    if (content[pos] == '{') {
        memmove(content + strlen(username) + 3, content + pos + 2, length - pos - 1);
        memcpy(content + pos, username, strlen(username));
        content[pos + strlen(username)] = '}';
        content[length + strlen(username)] = '\0';
    }

    return content;
}

char* hello(RequestContext *context) {
    return render_template("hello.html", context->username);
}

void bind_route(const char *route, char* (*handler)(RequestContext *)) {
    RequestContext context = { .username = "world" }; // Example username
    if (strcmp(route, "/hello/world") == 0) {
        char *response = handler(&context);
        printf("%s\n", response); // Simulate sending the response
        free(response);
    }
}

int main() {
    bind_route("/hello/world", hello);
    return 0;
}