#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

typedef struct {
    char *content;
} Template;

Template* render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    Template *template = (Template*)malloc(sizeof(Template));
    template->content = (char*)malloc(length + strlen(username) + 10); // extra for safety
    char *buffer = (char*)malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    sprintf(template->content, buffer, username);
    free(buffer);
    return template;
}

void hello(RequestContext *request) {
    Template *template = render_template("hello.html", request->username);
    printf("%s\n", template->content);
    free(template->content);
    free(template);
}

void route_handler(const char *url, const char *username) {
    if (strcmp(url, "/hello/") == 0) {
        RequestContext *request = (RequestContext*)malloc(sizeof(RequestContext));
        request->username = strdup(username);
        hello(request);
        free(request->username);
        free(request);
    }
}

int main() {
    route_handler("/hello/", "JohnDoe");
    return 0;
}