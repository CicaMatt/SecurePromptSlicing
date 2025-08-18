#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Request;

typedef struct {
    Request* request;
} Environment;

typedef struct {
    char* content;
} Response;

char* get_template() {
    return "<html><body>Hello, %s!</body></html>";
}

Response render_response_from_env(Environment* env) {
    char* template = get_template();
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, env->request->name);

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
    env.request = &request;

    Response response = home(&env);

    printf("%s\n", response.content);

    free(response.content);
    return 0;
}