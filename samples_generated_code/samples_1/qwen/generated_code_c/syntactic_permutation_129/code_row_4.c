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

Response render_template(const char *template, const char *name) {
    char *content = malloc(strlen(template) + strlen(name) + 1);
    sprintf(content, template, name);
    return (Response){.content = content};
}

const char* get_parameter(const Request *request, const char *param_name) {
    if (strcmp(param_name, "name") == 0) {
        return request->name;
    }
    return NULL;
}

Response render_response_from_env(const Environment *env, const Request *req) {
    const char *name = get_parameter(req, "name");
    return render_template(env->template, name);
}

Response home(const Environment *env, const Request *req) {
    return render_response_from_env(env, req);
}

int main() {
    Environment env = {.template = "Hello, %s!"};
    Request req = {.name = "World"};
    Response resp = home(&env, &req);
    printf("%s\n", resp.content);
    free((void*)resp.content); // Free the allocated memory
    return 0;
}