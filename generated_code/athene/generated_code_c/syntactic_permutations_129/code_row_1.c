#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *content;
} Response;

Response* render_response_from_env(Environment *env, Request *req) {
    char name[100];
    if (req->name != NULL) {
        strncpy(name, req->name, 99);
    } else {
        strcpy(name, "World");
    }
    
    const char *template = env->template;
    char rendered_template[256];
    snprintf(rendered_template, sizeof(rendered_template), template, name);

    Response *response = (Response *)malloc(sizeof(Response));
    response->content = strdup(rendered_template);
    return response;
}

Response* home(Environment *env) {
    Request req = { .name = "User" }; // Example request with a name
    return render_response_from_env(env, &req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Response *response = home(&env);
    printf("%s\n", response->content);
    free((void *)response->content);
    free(response);
    return 0;
}