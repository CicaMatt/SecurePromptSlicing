#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request request;
} Environment;

typedef struct {
    char* template;
} Template;

typedef struct {
    char* content;
} Response;

Template get_template(Environment* env) {
    Template tmpl;
    tmpl.template = "Hello, %s!";
    return tmpl;
}

Response render_response_from_env(Environment* env) {
    Template tmpl = get_template(env);
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), tmpl.template, env->request.name);

    Response response;
    response.content = strdup(buffer);
    return response;
}

Response home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Request request;
    request.name = "World";

    Environment env;
    env.request = request;

    Response response = home(&env);

    printf("%s\n", response.content);
    free(response.content);

    return 0;
}