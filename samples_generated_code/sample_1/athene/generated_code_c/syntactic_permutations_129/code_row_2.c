#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response render_response_from_env(Environment *env) {
    char *request = getenv("QUERY_STRING");
    char name[100] = "World";
    if (request && strstr(request, "name=")) {
        sscanf(request, "name=%[^&]", name);
    }
    
    const char *template = env->template;
    int len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    sprintf(rendered, template, name);

    Response response = { .content = rendered };
    return response;
}

void home(Environment *env) {
    Response resp = render_response_from_env(env);
    printf("Content-Type: text/html\n\n");
    printf("%s", resp.content);
    free((char *)resp.content);
}

int main() {
    Environment env = { .template = "<h1>Hello, %s!</h1>" };
    home(&env);
    return 0;
}