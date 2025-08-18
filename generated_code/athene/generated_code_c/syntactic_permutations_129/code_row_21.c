#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    Request *request;
    const char *template;
} Environment;

typedef struct {
    char *content;
} Response;

char* get_parameter(Request *req, const char *key) {
    if (strcmp(key, "name") == 0 && req->name != NULL) {
        return strdup(req->name);
    }
    return NULL;
}

Response* render_template(const char *template, const char *name) {
    Response *response = malloc(sizeof(Response));
    response->content = malloc(1024); // Simplified allocation
    snprintf(response->content, 1023, template, name);
    return response;
}

Response* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env->request, "name");
    if (name == NULL) {
        name = "World";
    }
    Response *response = render_template(env->template, name);
    free((void*)name); // Free the duplicated string
    return response;
}

Response* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    Request request;
    request.name = "User";
    env.request = &request;
    env.template = "Hello, %s!";
    
    Response *response = home(&env);
    printf("%s\n", response->content);

    free(response->content);
    free(response);

    return 0;
}